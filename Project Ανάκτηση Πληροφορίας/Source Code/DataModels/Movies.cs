
using Nest;

using System.Collections.Generic;

namespace Anaktisi
{
    /// <summary>
    /// The class that describes a row in the movies csv file
    /// </summary>
    [ElasticsearchType(IdProperty = nameof(MoviesId))]
    public class Movies
    {
        #region Public Properties

        /// <summary>
        /// The id of the movie
        /// </summary>
        public int MoviesId { get; set; }

        /// <summary>
        /// The title of the movie
        /// </summary>
        [Text(Similarity = "BM25")]
        public string Title { get; set; }

        /// <summary>
        /// The genres that the movie is associated with
        /// </summary>
        public List<string> Genres { get; set; }

        #endregion

        #region Constructors

        /// <summary>
        /// Default constructor
        /// </summary>
        public Movies()
        {

        }

        #endregion
    }
}
