namespace Anaktisi
{
    /// <summary>
    /// The movie genres one hot encoding data model
    /// </summary>
    public class GenresOneHotEncodingDataModel
    {
        #region Public Properties

        /// <summary>
        /// The aggregated, using comma, genres
        /// </summary>
        public string AggregatedGenres { get; set; }

        #endregion

        #region Constructors

        /// <summary>
        /// Default constructor
        /// </summary>
        public GenresOneHotEncodingDataModel()
        {

        }

        #endregion
    }
}
