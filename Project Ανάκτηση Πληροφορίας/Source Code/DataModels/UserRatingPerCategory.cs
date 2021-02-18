namespace Anaktisi
{
    /// <summary>
    /// The category ratings per user
    /// </summary>
    public class UserRatingPerCategory
    {
        #region Public Properties

        /// <summary>
        /// The user id
        /// </summary>
        public int Id { get; set; }

        /// <summary>
        /// The rating per movie category
        /// </summary>
        public AverageRatingPerCategory RatingsPerCategory { get; set; }

        #endregion

        #region Constructors

        /// <summary>
        /// Default constructor
        /// </summary>
        public UserRatingPerCategory()
        {

        }

        #endregion
    }
}
