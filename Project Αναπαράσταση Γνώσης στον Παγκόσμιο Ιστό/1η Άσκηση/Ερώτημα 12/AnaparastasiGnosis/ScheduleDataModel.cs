using System.Linq;
using System.Xml.Serialization;

namespace AnaparastasiGnosis
{
    /// <summary>
    /// The xml representation of a <see cref="Schedule"/>
    /// </summary>
    [XmlRoot("Schedule")]
    public class ScheduleDataModel
    {
        #region Public Properties

        /// <summary>
        /// The schedule
        /// </summary>
        [XmlElement("Lesson")]
        public LessonDataModel[] Lessons { get; set; }

        #endregion

        #region Constructors

        /// <summary>
        /// Default constructor
        /// </summary>
        public ScheduleDataModel() : base()
        {

        }

        #endregion

        #region Public Methods

        /// <summary>
        /// Returns a string that represents the current object
        /// </summary>
        /// <returns></returns>
        public override string ToString() => (Lessons?.Count().ToString() ?? "0") + " lesson/s";

        /// <summary>
        /// Creates and returns a <see cref="Schedule"/> from the current <see cref="ScheduleDataModel"/>
        /// </summary>
        /// <returns></returns>
        public Schedule ToSchedule()
        {
            var schedule = new Schedule();

            foreach (var lesson in Lessons?.Select(x => x.ToLesson()) ?? Enumerable.Empty<Lesson>())
                schedule.Add(lesson);

            return schedule;
        }

        #endregion
    }
}
