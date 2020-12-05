using Atom.Core;
using Atom.Windows.Controls;

using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using System.Windows.Media;

namespace AnaparastasiGnosis
{
    public class SchedulePage : ConventionalBaseDataPresenterPage<Lesson>
    {
        #region Public Properties

        /// <summary>
        /// The schedule
        /// </summary>
        public Schedule Schedule { get; private set; }

        #endregion

        #region Protected Properties

        /// <summary>
        /// The add button
        /// </summary>
        protected IconButton AddButton { get; private set; }

        #endregion

        #region Constructors

        /// <summary>
        /// Default constructor
        /// </summary>
        public SchedulePage() : base()
        {
            CreateGUI();
        }

        #endregion

        #region Protected Methods

        /// <summary>
        /// Creates and returns the <see cref="BaseItemsControlPage{TClass}.DataPresenter"/>
        /// </summary>
        /// <returns></returns>
        protected override IDataPresenter<Lesson> CreateDataPresenter()
        {
            // Create the data grid
            var lessonsDataGrid = new CollapsibleDataGrid<Lesson>();

            lessonsDataGrid.ShowData(x => x.Title)
                    .ShowData(x => x.Lectures)
                    .ShowData(x => x.Professor)
                    
                    .SetDataPresenterSubElement(x => x.Lectures, lesson => lesson.Lectures.Count().ToString("lecture", "lectures", "No lectures"), 
                    lesson => 
                    {
                        // Create the lectures data grid
                        var lecturesDataGrid = new DataGrid<Lecture>();

                        lecturesDataGrid.ShowData(x => x.Classroom)
                                        .ShowData(x => x.Day)
                                        .ShowData(x => x.TimeStart)
                                        .ShowData(x => x.TimeEnd)

                                        .SetLabelUIElement(x => x.Day, x => x.Day.ToLocalizedString(), x => x.Day.ToColorHex())
                                        
                                        .SetEditOption(() => 
                                        {
                                            return new DataForm<Lecture>()
                                                .ShowInput(x => x.Classroom, null, true)
                                                .ShowCustomInput(x => x.Day, (dataForm, propertyInfo) => new DropDownMenuEnumOptionsFormInput<DayOfWeek>(dataForm, propertyInfo, x => x.ToLocalizedString()), false, null, true)
                                                .ShowInput(x => x.TimeStart)
                                                .ShowInput(x => x.TimeEnd);
                                        }, "Lecture modification", null, async lecture => await Schedule.SaveChangesAsync())
                                        .SetDeleteOption("Lecture deletion", null, async lecture => 
                                        {
                                            lesson.Remove(lecture);

                                            return await Schedule.SaveChangesAsync();
                                        });

                        // Return the lectures data grid
                        return lecturesDataGrid;
                    },
                    (presenter, lesson, button) => 
                    {
                        button.PathData = IconPaths.PlusPath;

                        button.Command = new RelayCommand(async () =>
                        {
                            // Create the form
                            var form = new DataForm<Lecture>(new Lecture())
                                .ShowInput(x => x.Classroom, null, true)
                                .ShowSelectEnumSingleOptionInput(x => x.Day, (dataForm, propertyInfo) => new DropDownMenuEnumOptionsFormInput<DayOfWeek>(dataForm, propertyInfo, x => x.ToLocalizedString()), null, true)
                                .ShowInput(x => x.TimeStart)
                                .ShowInput(x => x.TimeEnd);

                            // Show the dialog
                            var dialogResult = await DialogHelpers.ShowConventionalAddDialogAsync(this, "Lecture creation", null, form);

                            // If we didn't get positive feedback...
                            if (!dialogResult.Feedback)
                                // Return
                                return;

                            // Add it
                            lesson.Add(form.Model);

                            // Save the changes
                            var result = await Schedule.SaveChangesAsync();

                            // If there was an error...
                            if (!result.Successful)
                            {
                                // Show the error
                                await result.ShowDialogAsync(this);

                                // Return
                                return;
                            }

                            // Add it to the data presenter
                            presenter.Add(form.Model);

                            // Show a changes saved dialog
                            await DialogHelpers.ShowChangesSavedHintDialogAsync(this);
                        });
                    })
                    
                    .SetEditOption(() => 
                    {
                        return new DataForm<Lesson>()
                            .ShowInput(x => x.Title, null, true)
                            .ShowInput(x => x.Professor, null, true);
                    }, "Lesson modification", null, async lesson => await Schedule.SaveChangesAsync())
                    .SetDeleteOption("Lesson deletion", null, async lesson => 
                    {
                        Schedule.Remove(lesson);

                        return await Schedule.SaveChangesAsync();
                    });

            // Return it
            return lessonsDataGrid;
        }

        /// <summary>
        /// Gets all the data
        /// </summary>
        /// <returns></returns>
        protected override Task<IFailable<IEnumerable<Lesson>>> GetAllDataAsync()
        {
            try
            {
                // Get the data
                var data = XMLHelpers.FromXmlFile<ScheduleDataModel>(Constants.File);

                // Create the schedule
                Schedule = data.ToSchedule();

                // Return the lessons
                return Task.FromResult<IFailable<IEnumerable<Lesson>>>(new Failable<IEnumerable<Lesson>>(Schedule.Lessons));
            }
            catch(Exception ex)
            {
                return Task.FromResult<IFailable<IEnumerable<Lesson>>>(new Failable<IEnumerable<Lesson>>() { ErrorMessage = ex.Message });
            }
        }

        #endregion

        #region Private Methods

        /// <summary>
        /// Creates and adds the required GUI elements
        /// </summary>
        private void CreateGUI()
        {
            Background = Brushes.White;

            // Create the add button
            AddButton = ControlsFactory.CreateStandardAddCircularButton();

            AddButton.Command = new RelayCommand(async () =>
            {
                // Create the form
                var form = new DataForm<Lesson>(new Lesson())
                    .ShowInput(x => x.Title, null, true)
                    .ShowInput(x => x.Professor, null, true);

                // Show the dialog
                var dialogResult = await DialogHelpers.ShowConventionalAddDialogAsync(this, "Lesson creation", null, form, IconPaths.PlusPath);

                // If we didn't get positive feedback...
                if (!dialogResult.Feedback)
                    // Return
                    return;

                // Add the lesson
                Schedule.Add(form.Model);

                // Save the changes
                var result = await Schedule.SaveChangesAsync();

                // If there was an error...
                if (!result.Successful)
                {
                    // Show the error
                    await result.ShowDialogAsync(this);

                    // Return
                    return;
                }

                // Add it to the data presenter
                DataPresenter.Add(form.Model);

                // Show a changes saved dialog
                await DialogHelpers.ShowChangesSavedHintDialogAsync(this);
            });
            
            // Add it to the content grid
            ContentGrid.Children.Add(AddButton);
        }

        #endregion
    }
}
