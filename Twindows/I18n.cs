using System;
using System.ComponentModel;
using System.Globalization;
using System.Resources;

namespace Twindows
{
    public class I18n : INotifyPropertyChanged
    {
        private readonly ResourceManager manager;

        private static readonly Lazy<I18n> lazy = new Lazy<I18n>(() => new I18n());

        public static I18n Instance => lazy.Value;

        public event PropertyChangedEventHandler PropertyChanged;

        public I18n()
        {
            manager = new ResourceManager("Twindows.Resources.i18n", typeof(I18n).Assembly);
        }

        // Removed nullable reference type annotation
        public string this[string name]
        {
            get
            {
                // Explicit null check added
                if (name == null)
                {
                    throw new ArgumentNullException(nameof(name));
                }
                return manager.GetString(name) ?? string.Empty;
            }
        }

        public void ApplyLanguage(CultureInfo cultureInfo)
        {
            CultureInfo.CurrentCulture = cultureInfo;
            CultureInfo.CurrentUICulture = cultureInfo;
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs("Item[]")); // Corrected event argument
        }
    }
}