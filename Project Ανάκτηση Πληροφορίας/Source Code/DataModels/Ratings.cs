using KerasModel;

using Nest;

using System;

namespace Anaktisi
{
    /// <summary>
    /// The class that describes a row in the ratings csv file
    /// </summary>
    [ElasticsearchType(IdProperty = nameof(RatingId))]
    public class Ratings
    {
        #region Public Properties

        /// <summary>
        /// The unique rating id
        /// </summary>
        public Guid RatingId { get; }

        /// <summary>
        /// The user id
        /// </summary>
        public int UserId { get; set; }

        /// <summary>
        /// The movie id
        /// </summary>
        public int MovieId { get; set; }

        /// <summary>
        /// The rating of the movie
        /// </summary>
        public float Rating { get; set; }

        /// <summary>
        /// The time stamp of the rating
        /// </summary>
        public long Timestamp { get; set; }

        #endregion

        #region Constructors

        /// <summary>
        /// Default constructor
        /// </summary>
        public Ratings()
        {
            RatingId = Guid.NewGuid();
        }

        #endregion

        #region Public Methods

        /// <summary>
        /// Return the <see cref="Options"/> based on the <see cref="Ratings"/>
        /// </summary>
        /// <returns></returns>
        public Options ToOptions()
        {
            return new Options()
            {
                MovieId = MovieId,
                Rating = Rating,
                UserId = UserId
            };
        }

        #endregion
    }
}
