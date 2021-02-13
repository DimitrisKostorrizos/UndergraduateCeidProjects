namespace Anaktisi
{
    /// <summary>
    /// The transformed movie genres one hot encoding data model
    /// </summary>
    public class TransformedGenresOneHotEncodingDataModel
    {
        #region Public Properties

        /// <summary>
        /// The one hot encoding transformation
        /// </summary>
        public float[] AggregatedGenres { get; set; }

        #endregion

        #region Constructors

        /// <summary>
        /// Default constructor
        /// </summary>
        public TransformedGenresOneHotEncodingDataModel()
        {

        }

        #endregion
    }
}
