using Atom.Core;

using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace AnaparastasiGnosis
{
    /// <summary>
    /// The schedule
    /// </summary>
    public class Schedule
    {
        #region Private Members

        /// <summary>
        /// The member of the <see cref="Lessons"/>
        /// </summary>
        private readonly List<Lesson> mLessons = new List<Lesson>();

        #endregion

        #region Public Properties

        /// <summary>
        /// The lessons
        /// </summary>
        public IEnumerable<Lesson> Lessons { get => mLessons; }

        #endregion

        #region Constructors

        /// <summary>
        /// Default constructor
        /// </summary>
        public Schedule() : base()
        {

        }

        #endregion

        #region Public Methods

        /// <summary>
        /// Saves the changes
        /// </summary>
        /// <returns></returns>
        public Task<IFailable> SaveChangesAsync()
        {
            try
            {
                var dataModel = ToDataModel();

                XMLHelpers.ToXmlFile(dataModel, Constants.File);

                return Task.FromResult<IFailable>(new Failable());
            }
            catch(Exception ex)
            {
                return Task.FromResult<IFailable>(new Failable() { ErrorMessage = ex.Message });
            }
        }

        /// <summary>
        /// Adds the specified <paramref name="lesson"/>
        /// </summary>
        /// <param name="lesson">The lesson</param>
        public void Add(Lesson lesson)
        {
            mLessons.Add(lesson);
        }

        /// <summary>
        /// Removes the specified <paramref name="lesson"/>
        /// </summary>
        /// <param name="lesson">The lesson</param>
        public void Remove(Lesson lesson)
        {
            mLessons.Remove(lesson);
        }

        /// <summary>
        /// Creates and returns a <see cref="ScheduleDataModel"/> from the current <see cref="Schedule"/>
        /// </summary>
        /// <returns></returns>
        public ScheduleDataModel ToDataModel()
        {
            return new ScheduleDataModel()
            {
                Lessons = Lessons.Select(x => x.ToDataModel()).ToArray()
            };
        }

        #endregion
    }
}
