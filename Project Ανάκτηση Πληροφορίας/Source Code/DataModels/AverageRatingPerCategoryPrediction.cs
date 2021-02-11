namespace Anaktisi
{
    /// <summary>
    /// The average rating per category prediction
    /// </summary>
    public class AverageRatingPerCategoryPrediction : AverageRatingPerCategory
    {
        #region Public Properties

        /// <summary>
        /// Predicted cluster label from the trainer
        /// </summary>
        public uint PredictedLabel { get; set; }

        #endregion

        #region Constructors

        /// <summary>
        /// Default constructor
        /// </summary>
        public AverageRatingPerCategoryPrediction()
        {

        }

        #endregion
    }
}
