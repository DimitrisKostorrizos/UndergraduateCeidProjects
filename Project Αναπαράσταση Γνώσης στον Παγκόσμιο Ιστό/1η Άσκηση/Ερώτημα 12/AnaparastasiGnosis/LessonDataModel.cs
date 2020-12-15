using System.Linq;
using System.Xml.Serialization;

namespace AnaparastasiGnosis
{
    /// <summary>
    /// The xml representation of a <see cref="Lesson"/>
    /// </summary>
    public class LessonDataModel
    {
        #region Public Properties

        /// <summary>
        /// The title
        /// </summary>
        public string Title { get; set; }

        /// <summary>
        /// The lectures
        /// </summary>
        [XmlElement("Lecture")]
        public LectureDataModel[] Lectures { get; set; }

        /// <summary>
        /// The professor
        /// </summary>
        public string Professor { get; set; }

        #endregion

        #region Constructors

        /// <summary>
        /// Default constructor
        /// </summary>
        public LessonDataModel() : base()
        {

        }

        #endregion

        #region Public Methods

        /// <summary>
        /// Returns a string that represents the current object
        /// </summary>
        /// <returns></returns>
        public override string ToString() => Title;

        /// <summary>
        /// Creates and returns a <see cref="Lesson"/> from the current <see cref="LessonDataModel"/>
        /// </summary>
        /// <returns></returns>
        public Lesson ToLesson()
        {
            var lesson = new Lesson()
            {
                Title = Title,
                Professor = Professor
            };

            foreach (var lecture in Lectures?.Select(x => x.ToLecture()) ?? Enumerable.Empty<Lecture>())
                lesson.Add(lecture);

            return lesson;
        }

        #endregion
    }
}
