using System.Collections.Generic;
using System.Linq;

namespace AnaparastasiGnosis
{
    /// <summary>
    /// Represents a lesson
    /// </summary>
    public class Lesson
    {
        #region Private Members 

        /// <summary>
        /// The member of the <see cref="Lectures"/> property
        /// </summary>
        private readonly List<Lecture> mLectures = new List<Lecture>();

        #endregion

        #region Public Properties

        /// <summary>
        /// The title
        /// </summary>
        public string Title { get; set; }

        /// <summary>
        /// The professor
        /// </summary>
        public string Professor { get; set; }

        /// <summary>
        /// The lectures
        /// </summary>
        public IEnumerable<Lecture> Lectures { get => mLectures; }

        #endregion

        #region Constructors

        /// <summary>
        /// Default constructor
        /// </summary>
        public Lesson() : base()
        {

        }

        #endregion

        #region Public Methods

        /// <summary>
        /// Adds the specified <paramref name="lecture"/>
        /// </summary>
        /// <param name="lecture">The lecture</param>
        public void Add(Lecture lecture)
        {
            mLectures.Add(lecture);
        }

        /// <summary>
        /// Removes the specified <paramref name="lecture"/>
        /// </summary>
        /// <param name="lecture">The lecture</param>
        public void Remove(Lecture lecture)
        {
            mLectures.Remove(lecture);
        }

        /// <summary>
        /// Returns a string that represents the current object
        /// </summary>
        /// <returns></returns>
        public override string ToString() => Title;

        /// <summary>
        /// Creates and returns the <see cref="LessonDataModel"/> from the current <see cref="Lesson"/>
        /// </summary>
        /// <returns></returns>
        public LessonDataModel ToDataModel()
        {
            return new LessonDataModel()
            {
                Professor = Professor,
                Title = Title,
                Lectures = Lectures.Select(x => x.ToDataModel()).ToArray()
            };
        }

        #endregion
    }
}
