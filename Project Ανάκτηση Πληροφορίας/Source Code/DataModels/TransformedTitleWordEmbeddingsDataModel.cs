namespace Anaktisi
{
    /// <summary>
    /// The transformed movie title word embedding data model
    /// </summary>
    public class TransformedTitleWordEmbeddingsDataModel : TitleWordEmbeddingsDataModel
    {
        #region Public Properties

        /// <summary>
        /// The word embeddings
        /// </summary>
        public float[] WordEmbeddings { get; set; }

        #endregion

        #region Constructors

        /// <summary>
        /// Default constructor
        /// </summary>
        public TransformedTitleWordEmbeddingsDataModel()
        {

        }

        #endregion
    }
}
