using Nest;

using System.Collections.Generic;
using System.Globalization;
using System.IO;
using System.Linq;

namespace Anaktisi
{
    /// <summary>
    /// The elastic search helper methods
    /// </summary>
    public static class ElasticsearchHelpers
    {
        /// <summary>
        /// Imports the movies data from the movies csv file
        /// </summary>
        /// <param name="filePath">The filepath to movies csv file</param>
        /// <returns>A list</returns>
        public static IEnumerable<Movies> ImportMoviesCsvData(string filePath)
        {
            // Read the csv file
            var rows = File.ReadAllLines(filePath).Select(x => x.Split(',')).Skip(1);

            // Declare a list for the movies
            var movies = new List<Movies>();

            // For each row...
            foreach (var line in rows)
            {
                // If the was a comma in the title...
                if (line.Count() != 3)
                {
                    // Concatenate the title parts
                    line[1] = line.Skip(1).Take(line.Length - 2).Aggregate((x, y) => x + "," + y);
                }

                // Add the new movie
                movies.Add(new Movies()
                {
                    MoviesId = int.Parse(line[0]),
                    Title = line[1],
                    Genres = new List<string>(line[^1].Split("|"))
                });
            }

            // Return the imported data
            return movies;
        }

        /// <summary>
        /// Imports the ratings data from the movies csv file
        /// </summary>
        /// <param name="filePath">The filepath to ratings csv file</param>
        /// <returns>A list</returns>
        public static IEnumerable<Ratings> ImportRatingsCsvData(string filePath)
        {
            // Read the csv file
            var rows = File.ReadAllLines(filePath).Select(x => x.Split(',')).Skip(1);

            // Declare a list for the ratings
            var ratings = new List<Ratings>();

            // For each row...
            foreach (var line in rows)
            {
                ratings.Add(new Ratings()
                {
                    UserId = int.Parse(line[0]),
                    MovieId = int.Parse(line[1]),
                    Rating = float.Parse(line[2], CultureInfo.InvariantCulture),
                    Timestamp = long.Parse(line[3])
                });
            }

            // Return the imported data
            return ratings;
        }

        /// <summary>
        /// Index the movies csv data if the index does not already exist
        /// </summary>
        /// <param name="client">The elastic search client</param>
        /// <param name="filePath">The filepath to movies csv file</param>
        /// <param name="indexName">The index name</param>
        /// <returns>Bool</returns>
        public static bool IndexMoviesCsvData(ElasticClient client, string filePath, string indexName)
        {
            // Check if the index exists
            var indexExistsResponse = client.Indices.Exists(indexName);

            // If the index does not exist...
            if (!indexExistsResponse.Exists)
            {
                // Import the movies csv data
                var movies = ImportMoviesCsvData(filePath);

                // Bulk index the movies data
                var moviesBulkIndexResponse = client.BulkIndexDocuments(movies, indexName);

                // If the bulk index response is valid..
                if (moviesBulkIndexResponse.IsValid)
                    // Return true
                    return true;
                else
                    // Return false
                    return false;
            }

            // Return true
            return true;
        }

        /// <summary>
        /// Index the ratings csv data if the index does not already exist
        /// </summary>
        /// <param name="client">The elastic search client</param>
        /// <param name="filePath">The filepath to ratings csv file</param>
        /// <param name="indexName">The index name</param>
        /// <returns>Bool</returns>
        public static bool IndexRatingsCsvData(ElasticClient client, string filePath, string indexName)
        {
            // Check if the index exists
            var indexExistsResponse = client.Indices.Exists(indexName);

            // If the index does not exist...
            if (!indexExistsResponse.Exists)
            {
                // Import the movies csv data
                var ratings = ImportRatingsCsvData(filePath);

                // Keep only the valid values
                ratings = ratings.Where(x => x.MovieId <= 9125).ToList();

                // Bulk index the ratings data
                var ratingsBulkIndexResponse = client.BulkIndexDocuments(ratings, indexName);

                // If the bulk index response is valid..
                if (ratingsBulkIndexResponse.IsValid)
                    // Return true
                    return true;
                else
                    // Return false
                    return false;
            }

            // Return true
            return true;
        }
    }
}
