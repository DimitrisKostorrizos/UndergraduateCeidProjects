
using System;
using System.Collections.Generic;

namespace Anaktisi
{
    /// <summary>
    /// A user's average rating per movie category
    /// </summary>
    public class AverageRatingPerCategory
    {
        #region Public Properties

        public float Adventure { get; set; }

        public float Animation { get; set; }

        public float Children { get; set; }

        public float Comedy { get; set; }

        public float Fantasy { get; set; }

        public float Romance { get; set; }

        public float Drama { get; set; }

        public float Action { get; set; }

        public float Crime { get; set; }

        public float Thriller { get; set; }

        public float Horror { get; set; }

        public float Mystery { get; set; }

        public float SciFi { get; set; }

        public float Documentary { get; set; }

        public float Imax { get; set; }

        public float War { get; set; }

        public float Musical { get; set; }

        public float Western { get; set; }

        public float FilmNoir { get; set; }

        public float NoGenresListed { get; set; }

        #endregion
    
        #region Constructors

        /// <summary>
        /// Default constructor
        /// </summary>
        public AverageRatingPerCategory()
        {

        }

        /// <summary>
        /// Standard constructor
        /// </summary>
        /// <param name="values">The values</param>
        public AverageRatingPerCategory(List<float> values)
        {
            _ = values ?? throw new ArgumentNullException();

            if (values.Count != 20)
                throw new ArgumentOutOfRangeException();

            Adventure = values[0];
            Animation = values[1];
            Children = values[2];
            Comedy = values[3];
            Fantasy = values[4];
            Romance = values[5];
            Drama = values[6];
            Action = values[7];
            Crime = values[8];
            Thriller = values[9];
            Horror = values[10];
            Mystery = values[11];
            SciFi = values[12];
            Documentary = values[13];
            Imax = values[14];
            War = values[15];
            Musical = values[16];
            Western = values[17];
            FilmNoir = values[18];
            NoGenresListed = values[19];
        }

        #endregion
    }
}
