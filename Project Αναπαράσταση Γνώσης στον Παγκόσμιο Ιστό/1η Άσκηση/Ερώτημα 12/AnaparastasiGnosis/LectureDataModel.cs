using Atom.Core;

using System;
using System.Xml.Serialization;

namespace AnaparastasiGnosis
{
    /// <summary>
    /// The xml representation of a <see cref="Lecture"/>
    /// </summary>
    public class LectureDataModel
    {
        #region Public Properties

        /// <summary>
        /// The classroom
        /// </summary>
        [XmlAttribute]
        public string Classroom { get; set; }

        /// <summary>
        /// The day
        /// </summary>
        public DayOfWeek Day { get; set; }

        /// <summary>
        /// The time span
        /// </summary>
        [XmlElement("Time")]
        public string TimeSpan { get; set; }

        #endregion

        #region Constructors

        /// <summary>
        /// Default constructor
        /// </summary>
        public LectureDataModel() : base()
        {

        }

        #endregion

        #region Public Methods

        /// <summary>
        /// Returns a string that represents the current object
        /// </summary>
        /// <returns></returns>
        public override string ToString() => $"{Classroom} {Day} {TimeSpan}";

        /// <summary>
        /// Creates and returns a <see cref="Lecture"/> from the current <see cref="LectureDataModel"/>
        /// </summary>
        /// <returns></returns>
        public Lecture ToLecture()
        {
            var timeStartParts = TimeSpan.Split('-')[0].Split(':');
            var timeEndParts = TimeSpan.Split('-')[1].Split(':');

            return new Lecture()
            {
                Classroom = Classroom,
                Day = Day,
                TimeStart = new Time(timeStartParts[0].ToInt(), timeStartParts[1].ToInt(), 0),
                TimeEnd = new Time(timeEndParts[0].ToInt(), timeEndParts[1].ToInt(), 0)
            };
        }

        #endregion
    }
}
