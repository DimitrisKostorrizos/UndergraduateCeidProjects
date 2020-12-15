using Atom.Windows.Controls;

using System.Windows;

namespace AnaparastasiGnosis
{
    /// <summary>
    /// The main window view model
    /// </summary>
    public class MainWindowViewModel : WindowViewModel
    {
        #region Constructors

        /// <summary>
        /// Default constructor
        /// </summary>
        public MainWindowViewModel(Window window) : base(window) => IsMain = true;

        #endregion
    }
}
