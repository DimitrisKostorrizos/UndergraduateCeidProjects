using Microsoft.ML;
using Microsoft.ML.Transforms.Text;

using Nest;

using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace Anaktisi
{
    public class Program
    {
        async static Task Main()
        {
            #region Question 1

            // Set the max response size
            var maxResponseDocumentsSize = 10000;

            // Define the file path to movies.csv
            var moviesFilePath = "C:/Users/jimak/Documents/GitHub/UndergraduateCeidProjects/Project Ανάκτηση Πληροφορίας/movies.csv";

            // Set the movie index name
            var moviesIndex = "moviesindex";

            // Create an instance to the client
            var client = new ElasticClient();

            // Index the movies csv file
            if (!ElasticsearchHelpers.IndexMoviesCsvData(client, moviesFilePath, moviesIndex))
                Console.WriteLine("Movies csv data indexing failed.");

            // Define the search word
            var searchWord = "Story";

            // Get the movies that contains similar words with the search word
            var moreLikeThisMoviesResponse = await client.SearchAsync<Movies>(x => x.Source(
                s => s.Includes(i => i.Fields(f => f.Title, fields => fields.MoviesId)))
            .Query(y => 
            y.MoreLikeThis(z => 
                z.Fields(a => a.Field(b => b.Title))
                .Like(c => c.Text(searchWord))
                .MinTermFrequency(1)))
            .Size(maxResponseDocumentsSize).Index(moviesIndex));

            // Get the descending order by score documents
            var moviesResults = moreLikeThisMoviesResponse.Documents.ToList();

            // For every movie...
            foreach (var movie in moviesResults)
                Console.WriteLine(movie.Title);

            Console.WriteLine();

            #endregion

            #region Question 2

            // Define the file path to movies.csv
            var ratingsFilePath = "C:/Users/jimak/Documents/GitHub/UndergraduateCeidProjects/Project Ανάκτηση Πληροφορίας/ratings.csv";

            // Set the ratings index name
            var ratingsIndex = "ratingsindex";

            // Index the movies csv file
            if (!ElasticsearchHelpers.IndexRatingsCsvData(client, ratingsFilePath, ratingsIndex))
                Console.WriteLine("Ratings csv data indexing failed.");

            // Define the user id
            var userId = 1;

            // Get the movies and the ratings of the user
            var userRatingsResponse = await client.SearchAsync<Ratings>(x => x
            .Source(s =>
                s.Includes(i => i.Fields(f => f.MovieId, f => f.Rating)))
            .Query(y =>
                y.Term(z => z.UserId, userId))
            .Size(maxResponseDocumentsSize).Index(ratingsIndex));

            // Get the descending order by score documents
            var ratingsResults = userRatingsResponse.Documents.ToList();

            // Declare a dictionary that will contain the movies and the new scores
            var resultDictionary = new Dictionary<Movies, double>();

            // For every movie...
            foreach (var movie in moviesResults)
            {
                // Get the user rating for the movie
                var userMovieRating = ratingsResults.FirstOrDefault(x => x.MovieId == movie.MoviesId);

                // Get the user rating
                var userRating = userMovieRating == null ? 0 : userMovieRating.Rating;

                // Get the movie ratings
                var movieRatingsResponse = await client.SearchAsync<Ratings>(x =>
                x.Source(s =>
                    s.Includes(i => i.Fields(f => f.Rating)))
                .Query(y =>
                    y.Term(z => z.MovieId, movie.MoviesId))
                .Index(ratingsIndex).Size(maxResponseDocumentsSize));

                // Get the movie rating
                var averageMovieRating = movieRatingsResponse.Documents.Count == 0 ? 0 : movieRatingsResponse.Documents.Select(x => x.Rating).Average();

                // Get the elastic search movie score
                var movieScore = moreLikeThisMoviesResponse.Hits.FirstOrDefault(x => x.Id == movie.MoviesId.ToString()).Score;

                // Add the new score per movie
                resultDictionary.Add(movie, userRating + averageMovieRating + movieScore.Value);
            }

            // Sort the dictionary based on the cumulative score
            var sortedResultDictionary = resultDictionary.OrderByDescending(x => x.Value);

            // Get the sorted movies
            var sortedUserMovies = sortedResultDictionary.Select(x => x.Key).ToList();

            // For every movie...
            foreach(var movie in sortedUserMovies)
                Console.WriteLine(movie.Title);

            Console.WriteLine();

            #endregion

            #region Question 3

            // Get all movies genres
            var allMovieCategoryResponse = await client.SearchAsync<Movies>(x =>
            x.Source(s => s.Includes(i => i.Fields(f => f.Genres)))
            .Query(c => c.MatchAll())
            .Index(moviesIndex).Size(maxResponseDocumentsSize));

            // Get the movie categories
            var movieCategories = allMovieCategoryResponse.Documents.SelectMany(x => x.Genres).Distinct().ToList();

            // Declare a dictionary that will contain the categories and the ids of the associated movies
            var movieIdsPerCategory = new Dictionary<string, List<int>>();

            // For every category...
            foreach (var category in movieCategories)
            {
                // Get the movie genres
                var genreMovieResponse = await client.SearchAsync<Movies>(x => x.Source(s =>
                s.Includes(i =>
                    i.Fields(f => f.MoviesId)))
                .Query(y =>
                    y.Match(z => z.Field(a => a.Genres).Query(category)))
                .Index(moviesIndex).Size(maxResponseDocumentsSize));

                // Get the movie ids that belong to the category
                var ids = genreMovieResponse.Documents.Select(x => x.MoviesId).ToList();

                // Add it
                movieIdsPerCategory.Add(category, ids);
            }

            // Get all the distinct user ids
            var allUserIdsResponse = await client.SearchAsync<Ratings>(x =>
            x.Source(s =>
            s.Includes(i => i.Fields(f => f.UserId)))
            .Query(y => y.MatchAll())
            .Collapse(x => x.Field(a => a.UserId))
            .Index(ratingsIndex).Size(maxResponseDocumentsSize));

            // Get the user ids
            var userIds = allUserIdsResponse.Documents.Select(x => x.UserId).ToList();

            // Declare a dictionary that will contain the user id and ratings per category
            var userStats = new List<UserRatingPerCategory>();

            // For every user id...
            foreach (var id in userIds)
            {
                // Declare a dictionary that will contain the rating per category
                var movieCategoryRatings = new List<float>();

                // For every category...
                foreach (var categoryKey in movieCategories)
                {
                    // Get the movie id collection per category
                    var movieIdCollectionPerCategory = movieIdsPerCategory.FirstOrDefault(x => x.Key == categoryKey).Value;

                    // Get all the ratings per category and user id
                    var movieRatingPerUserPerCategory = await client.SearchAsync<Ratings>(x =>
                    x.Source(s =>
                        s.Includes(i => i.Fields(f => f.Rating)))
                    .Query(y =>
                        y.Bool(b => b.Filter(fil =>
                            fil.Terms(m =>
                                m.Field(g => g.UserId).Terms(id)),
                            fil => fil.Terms(m => m
                                .Field(g => g.MovieId).Terms(movieIdCollectionPerCategory)))))
                    .Index(ratingsIndex).Size(maxResponseDocumentsSize));

                    // Calculate the average rating
                    var averageRating = movieRatingPerUserPerCategory.Documents.Count == 0 ? 0 : movieRatingPerUserPerCategory.Documents.Select(x => x.Rating).Average();

                    // Add the movie category rating
                    movieCategoryRatings.Add(averageRating);
                }

                // Create the user ratings per category and add it
                userStats.Add(new UserRatingPerCategory()
                {
                    Id = id,
                    RatingsPerCategory = new AverageRatingPerCategory(movieCategoryRatings)
                });
            }

            // Declare the features column names
            var featureColumnName = "Features";

            // Initialize a new machine learning context object and set the seed
            var machineLearningContext = new MLContext(0);

            // Initialize the number of clusters
            var numberOfClusters = 4;

            // Get the training data
            var averageRatingsTrainingData = machineLearningContext.Data.LoadFromEnumerable(userStats.Select(x => x.RatingsPerCategory));

            // Get the column names
            var propertyNames = typeof(AverageRatingPerCategory).GetProperties().Select(x => x.Name).ToArray();

            // Initialize the k-means trainer
            var kMeansTrainer = machineLearningContext.Transforms.Concatenate(featureColumnName, propertyNames)
            .Append(machineLearningContext.Clustering.Trainers.KMeans(featureColumnName, numberOfClusters: numberOfClusters));

            // Train the model
            var trainedAverageRatingsModel = kMeansTrainer.Fit(averageRatingsTrainingData);

            // Run the model on the same data set
            var transformedAverageRatingsData = trainedAverageRatingsModel.Transform(averageRatingsTrainingData);

            // Get the predictions
            var predictions = machineLearningContext.Data.CreateEnumerable<AverageRatingPerCategoryPrediction>(transformedAverageRatingsData, false).ToList();

            // Declare a dictionary for the cluster and the average ratings per category
            var clusteredUsersPerCluster = new List<List<int>>();

            // Declare a dictionary for the cluster and the average ratings per movie
            var averageMovieRatingPerCluster = new Dictionary<uint, List<float>>();

            // For every cluster...
            for (var index = 1u; index <= numberOfClusters; index++)
            {
                // Get the predictions that are clustered together
                var clusteredPredictions = predictions.FindAll(x => x.PredictedLabel == index);

                // Initialize a list for the average values per category
                var clusteredUsers = new List<UserRatingPerCategory>();

                // For every prediction...
                foreach (var prediction in clusteredPredictions)
                {
                    // Add the user stat that is contained in the cluster
                    clusteredUsers.Add(userStats.ElementAt(predictions.IndexOf(prediction)));
                }

                // Add the average rating of the category for the clustered users
                var clusteredUserIds = clusteredUsers.Select(x => x.Id).ToList();

                // Add the clustered ids
                clusteredUsersPerCluster.Add(clusteredUserIds);

                // Declare a list for the rating
                var averageMovierating = new List<float>();

                // For every movie...
                for (var movieId = 1; movieId <= 9125; movieId++)
                {
                    // Get the movie ratings for the clustered users
                    var clusteredUserRatings = await client.SearchAsync<Ratings>(x =>
                    x.Source(s =>
                        s.Includes(i => i.Fields(f => f.Rating)))
                    .Query(y =>
                        y.Bool(b => b.Filter(fil =>
                            fil.Terms(m =>
                                m.Field(g => g.UserId).Terms(clusteredUserIds)),
                            fil => fil.Terms(m => m
                                .Field(g => g.MovieId).Terms(movieId)))))
                    .Index(ratingsIndex).Size(maxResponseDocumentsSize));

                    // Calculate the average movie rating
                    var averageMovieRating = clusteredUserRatings.Documents.Count == 0 ? 0 : clusteredUserRatings.Documents.Select(x => x.Rating).Average();
                    
                    // Add it
                    averageMovierating.Add(averageMovieRating);
                }

                // Add the average movies ratings per cluster
                averageMovieRatingPerCluster.Add(index, averageMovierating);
            }

            // Declare a new list for the ratings
            var completeRatingsList = new List<Ratings>();

            // For every user id...
            foreach (var id in userIds)
            {
                // Get the rating for per user
                var movieRatingResponse = await client.SearchAsync<Ratings>(x =>
                    x.Query(y =>
                        y.Terms(z =>
                            z.Field(g => g.UserId).Terms(id)))
                    .Index(ratingsIndex).Size(maxResponseDocumentsSize));

                // Get the movie ids that have been already rated
                var alreadyRatedMovieIds = movieRatingResponse.Documents.Select(x => x.MovieId).ToList();

                // Add the rating to the list
                completeRatingsList.AddRange(movieRatingResponse.Documents);

                // Get the average rating for the user
                var averageRatingsPerCluster = averageMovieRatingPerCluster.ElementAt(clusteredUsersPerCluster.IndexOf(clusteredUsersPerCluster.Find(x => x.Contains(id)))).Value;

                // For every movie...
                for (var index = 1; index <= 9125; index++)
                {
                    // If the rating is already created...
                    if (alreadyRatedMovieIds.Contains(index))
                        continue;

                    // Add the new rating
                    completeRatingsList.Add(new Ratings()
                    {
                        MovieId = index,
                        UserId = id,
                        Rating = averageRatingsPerCluster.ElementAt(index - 1),
                        Timestamp = 0
                    });
                }
            }

            #endregion

            #region Question 4

            // Get the options
            var options = completeRatingsList.Select(x => x.ToOptions()).ToList();

            // Get all the movie titles response
            var allTitlesResponse = await client.SearchAsync<Movies>(x =>
            x.Source(s =>
            s.Includes(i => i.Fields(f => f.Title)))
            .Query(y => y.MatchAll())
            .Index(moviesIndex).Size(maxResponseDocumentsSize));

            // Get the titles
            var titleWordEmbeddings = new List<TitleWordEmbeddingsDataModel>();

            // Get the empty train data
            var emptyTrainData = machineLearningContext.Data.LoadFromEnumerable(titleWordEmbeddings);

            // For every title...
            foreach (var title in allTitlesResponse.Documents.Select(x => x.Title))
                // Add the title word embeddings
                titleWordEmbeddings.Add(new TitleWordEmbeddingsDataModel() 
                {
                    Title = title 
                });

            // Initialize the word embeddings trainer
            var titleWordEmbeddingsTrainer = machineLearningContext.Transforms.Text.NormalizeText("Title")
                .Append(machineLearningContext.Transforms.Text.TokenizeIntoWords("Tokens", "Title"))
                .Append(machineLearningContext.Transforms.Text.ApplyWordEmbedding("WordEmbeddings",
                    "Tokens", WordEmbeddingEstimator.PretrainedModelKind.SentimentSpecificWordEmbedding));

            // Fit to the empty data
            var textTransformer = titleWordEmbeddingsTrainer.Fit(emptyTrainData);

            // Create the prediction engine to get the embedding vector from the input string
            var predictionEngine = machineLearningContext.Model.CreatePredictionEngine<TitleWordEmbeddingsDataModel, TransformedTitleWordEmbeddingsDataModel>(textTransformer);

            // Declare a list that will contain the word embeddings prediction
            var wordEmbeddingsPrediction = new List<TransformedTitleWordEmbeddingsDataModel>();

            // Get the word embeddings
            var wordEmbeddings = wordEmbeddingsPrediction.Select(x => x.WordEmbeddings).ToList();

            // For every title...
            foreach (var instanse in titleWordEmbeddings)
                // Add the word embeddings
                wordEmbeddingsPrediction.Add(predictionEngine.Predict(instanse));

            // Get all the movie genres response
            var allGenresResponse = await client.SearchAsync<Movies>(x =>
            x.Source(s =>
            s.Includes(i => i.Fields(f => f.Genres)))
            .Query(y => y.MatchAll())
            .Index(moviesIndex).Size(maxResponseDocumentsSize));

            // Declare a list that will contain the aggregated genres
            var aggregatedGenres = new List<GenresOneHotEncodingDataModel>();

            // Foe every genres list...
            foreach (var instance in allGenresResponse.Documents.Select(x => x.Genres))
                // Add the aggregated, using comma, genres
                aggregatedGenres.Add(new GenresOneHotEncodingDataModel() 
                {
                    AggregatedGenres = instance.Aggregate((x, y) => x + "," + y)
                });

            // Convert aggregated genres to training data
            var genresTrainingData = machineLearningContext.Data.LoadFromEnumerable(aggregatedGenres);

            // Initialize the one hot encoding trainer
            var oneHotEncodingTrainer = machineLearningContext.Transforms.Categorical.OneHotEncoding(
                    new[]
                    {
                        new InputOutputColumnPair("AggregatedGenres")
                    });

            // Fit and transform the data
            var transformedOneHotEncodingData = oneHotEncodingTrainer.Fit(genresTrainingData).Transform(genresTrainingData);

            // Get the one hot encoding transformations
            var oneHotEncodingTransformations = machineLearningContext.Data.CreateEnumerable<TransformedGenresOneHotEncodingDataModel>(transformedOneHotEncodingData, true);

            // Get the one hot encodings maps
            var oneHotEncodingMaps = oneHotEncodingTransformations.Select(x => x.AggregatedGenres).ToList();

            #endregion
        }
    }
}
