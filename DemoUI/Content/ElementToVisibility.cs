using System;
using System.Collections.Generic;
using System.Globalization;
using System.Windows.Data;
using System.Windows;

namespace DemoUI
{
    public class ElementToVisibility : IValueConverter
    {
        public object Convert(object value, Type targetType, object parameter, CultureInfo culture)
        {
            bool isVisible = (bool)value;

            Visibility visibility = (Visibility) parameter;

            if(isVisible)
            {
                visibility = Visibility.Visible;
            }
            else
            {
                visibility = Visibility.Hidden;
            }
            return visibility;
        }

        public object ConvertBack(object value, Type targetType, object parameter, CultureInfo culture)
        {
            throw new NotImplementedException();
        }
    }
}
