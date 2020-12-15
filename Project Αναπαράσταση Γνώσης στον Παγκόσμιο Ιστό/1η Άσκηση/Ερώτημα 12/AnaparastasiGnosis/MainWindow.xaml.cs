using Atom.Core;
using Atom.Windows;
using Atom.Windows.Controls;
using Atom.Windows.Controls.TabControl;

using System.Windows;

namespace AnaparastasiGnosis
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        #region Protected Properties

        /// <summary>
        /// The dialogs contains
        /// </summary>
        protected DialogOverlayContainer<SchedulePage> DialogsContainer { get; private set; }

        /// <summary>
        /// The schedule page
        /// </summary>
        protected SchedulePage SchedulePage { get; private set; }

        #endregion

        #region Constructors

        /// <summary>
        /// Default constructor
        /// </summary>
        public MainWindow()
        {
            // Initialize the DI
            var construction = Framework.Construct<DefaultFrameworkConstruction>()
                     .AddControlManager()
                     .AddTaskManager()
                     .AddDialogManager();

            construction.Build();

            InitializeComponent();

            DataContext = new MainWindowViewModel(this)
            {
                Title = "Knowledge presentation"
            };

            #region Dialogs Container

            // Create the dialogs container
            DialogsContainer = new DialogOverlayContainer<SchedulePage>();

            // Create the page
            SchedulePage = new SchedulePage();

            DialogsContainer.Content = SchedulePage;

            // Set it as the content
            Content = DialogsContainer;

            #endregion
        }

        #endregion
    }
}
