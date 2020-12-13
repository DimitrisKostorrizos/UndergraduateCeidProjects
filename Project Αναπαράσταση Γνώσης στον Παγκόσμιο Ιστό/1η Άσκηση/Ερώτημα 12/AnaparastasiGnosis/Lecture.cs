using Atom.Core;

using System;

namespace AnaparastasiGnosis
{
    /// <summary>
    /// Represents a lecture
    /// </summary>
    public class Lecture
    {
        #region Public Properties

        /// <summary>
        /// The day of week
        /// </summary>
        public DayOfWeek Day { get; set; }

        /// <summary>
        /// The time start
        /// </summary>
        public Time TimeStart { get; set; }

        /// <summary>
        /// The time end
        /// </summary>
        public Time TimeEnd { get; set; }

        /// <summary>
        /// The classroom
        /// </summary>
        public string Classroom { get; set; }

        #endregion

        #region Constructors

        /// <summary>
        /// Default constructor
        /// </summary>
        public Lecture() : base()
        {

        }

        #endregion

        #region Public Methods

        /// <summary>
        /// Creates and returns a <see cref="LectureDataModel"/> from the current <see cref="Lecture"/>
        /// </summary>
        /// <returns></returns>
        public LectureDataModel ToDataModel()
        {
            return new LectureDataModel()
            {
                Classroom = Classroom,
                Day = Day,
                TimeSpan = TimeStart.HourMinuteString(false) + "-" + TimeEnd.HourMinuteString(false)
            };
        }

        #endregion
    }
}
