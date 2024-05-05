﻿using Microsoft.Win32;
using System;
using System.Diagnostics;
using System.Runtime.InteropServices;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;
using System.Windows.Interop;
using System.Windows.Media;

namespace Twindows
{
    /// <summary>
    /// MainWindow.xaml etkileşim mantığı
    /// </summary>
    public partial class MainWindow : Window
    {
        const string cur_ver = "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\";
        [DllImport("user32.dll")]
        internal static extern int SetWindowCompositionAttribute(IntPtr hwnd, ref WindowCompositionAttributeData data);
        [DllImport("dwmapi.dll")]
        internal static extern int DwmSetWindowAttribute(IntPtr hwnd, int attr, int[] attrValue, int attrSize);

        [StructLayout(LayoutKind.Sequential)]
        internal struct AccentPolicy
        {
            public uint AccentState;
            public uint AccentFlags;
            public uint GradientColor;
            public uint AnimationId;
        }

        [StructLayout(LayoutKind.Sequential)]
        internal struct WindowCompositionAttributeData
        {
            public int Attribute;
            public IntPtr Data;
            public int SizeOfData;
        }

        public MainWindow()
        {
            InitializeComponent();
            InitializeKeys();
            EnableBlur();
        }

        internal void EnableBlur()
        {
            EnableBlur(null, null);
        }

        internal void EnableBlur(object sender, RoutedEventArgs e)
        {
            var accent = new AccentPolicy()
            {
                AccentFlags = 2,
                AccentState = 4,
                GradientColor = 0x00000050
            };

            var accentPtr = Marshal.AllocHGlobal(Marshal.SizeOf(accent));
            Marshal.StructureToPtr(accent, accentPtr, false);

            var data = new WindowCompositionAttributeData()
            {
                Attribute = 19,
                SizeOfData = Marshal.SizeOf(accent),
                Data = accentPtr,
            };

            SetWindowCompositionAttribute(new WindowInteropHelper(this).Handle, ref data);
            Marshal.FreeHGlobal(accentPtr);
        }

        private void Close(object sender, RoutedEventArgs e)
        {
            try
            {
                Close();
            }
            catch { } 
        }

        private void Github(object sender, System.Windows.Input.MouseButtonEventArgs e)
        {
            try
            {
                Process.Start("https://github.com/shadesofdeath");
            }
            catch { }       
        }
        private void InitializeKeys()
        {
            // https://www.elevenforum.com/t/disable-ads-in-windows-11.8004/
            // Sync provider notifications in File Explorer
            bool key1 = CreateKey(cur_ver + "Explorer\\Advanced", "ShowSyncProviderNotifications");
            cb1.IsChecked = !key1;

            // Get fun facts, tips, tricks, and more on your lock screen
            bool key2 = CreateKey(cur_ver + "ContentDeliveryManager", "RotatingLockScreenOverlayEnabled");
            bool key3 = CreateKey(cur_ver + "ContentDeliveryManager", "SubscribedContent-338387Enabled");
            cb2.IsChecked = !key2 && !key3;

            // Show suggested content in Settings app
            bool key4 = CreateKey(cur_ver + "ContentDeliveryManager", "SubscribedContent-338393Enabled");
            bool key5 = CreateKey(cur_ver + "ContentDeliveryManager", "SubscribedContent-353694Enabled");
            bool key6 = CreateKey(cur_ver + "ContentDeliveryManager", "SubscribedContent-353696Enabled");
            cb3.IsChecked = !key4 && !key5 && !key6;

            // Get tips and suggestions when using Windows
            bool key7 = CreateKey(cur_ver + "ContentDeliveryManager", "SubscribedContent-338389Enabled");
            cb4.IsChecked = !key7;

            // Suggest ways to get the most out of Windows and finish setting up this device
            bool key8 = CreateKey(cur_ver + "UserProfileEngagement", "ScoobeSystemSettingEnabled");
            cb5.IsChecked = !key8;

            // Show me the Windows welcome experience after updates and occasionally when I sign in to highlight what's new and suggested
            bool key9 = CreateKey(cur_ver + "ContentDeliveryManager", "SubscribedContent-310093Enabled");
            cb6.IsChecked = !key9;

            // Let apps show me personalized ads by using my advertising ID
            bool key10 = CreateKey(cur_ver + "AdvertisingInfo", "Enabled");
            cb7.IsChecked = !key10;

            // Tailored experiences
            bool key11 = CreateKey(cur_ver + "Privacy", "TailoredExperiencesWithDiagnosticDataEnabled");
            cb8.IsChecked = !key11;

            // "Show recommendations for tips, shortcuts, new apps, and more" on Start
            bool key12 = CreateKey(cur_ver + "Explorer\\Advanced", "Start_IrisRecommendations");
            cb9.IsChecked = !key12;
        }

        private static bool CreateKey(string loc, string key)
        {
            RegistryKey keyRef = Registry.CurrentUser.OpenSubKey(loc, true);
            if (keyRef != null)
            {
                if (keyRef.GetValue(key) == null)
                {
                    keyRef.SetValue(key, 0);
                    keyRef.Close();
                    return false;
                }
                else
                {
                    return (Convert.ToInt32(keyRef.GetValue(key)) != 0);
                }
            }
            else
            {
                keyRef = Registry.CurrentUser.CreateSubKey(loc);
                if (keyRef != null)
                {
                    keyRef.SetValue(key, 0);
                    keyRef.Close();
                    return false;
                }
                else
                {
                    MessageBox.Show("Null KeyRef Used", "Fatal Error 2", MessageBoxButton.OK, MessageBoxImage.Error);
                    throw new InvalidOperationException("Null KeyRef Used While Creating Key");
                }
            }
        }

        private static bool ToggleOptions(string name, bool enable)
        {
            int value = Convert.ToInt32(!enable);

            switch (name)
            {
                case "cb1":
                    Registry.SetValue("HKEY_CURRENT_USER\\" + cur_ver + "Explorer\\Advanced\\", "ShowSyncProviderNotifications", value);
                    break;
                case "cb2":
                    Registry.SetValue("HKEY_CURRENT_USER\\" + cur_ver + "ContentDeliveryManager", "RotatingLockScreenOverlayEnabled", value);
                    Registry.SetValue("HKEY_CURRENT_USER\\" + cur_ver + "ContentDeliveryManager", "SubscribedContent-338387Enabled", value);
                    break;
                case "cb3":
                    Registry.SetValue("HKEY_CURRENT_USER\\" + cur_ver + "ContentDeliveryManager", "SubscribedContent-338393Enabled", value);
                    Registry.SetValue("HKEY_CURRENT_USER\\" + cur_ver + "ContentDeliveryManager", "SubscribedContent-353694Enabled", value);
                    Registry.SetValue("HKEY_CURRENT_USER\\" + cur_ver + "ContentDeliveryManager", "SubscribedContent-353696Enabled", value);
                    break;
                case "cb4":
                    Registry.SetValue("HKEY_CURRENT_USER\\" + cur_ver + "ContentDeliveryManager", "SubscribedContent-338389Enabled", value);
                    break;
                case "cb5":
                    Registry.SetValue("HKEY_CURRENT_USER\\" + cur_ver + "UserProfileEngagement", "ScoobeSystemSettingEnabled", value);
                    break;
                case "cb6":
                    Registry.SetValue("HKEY_CURRENT_USER\\" + cur_ver + "ContentDeliveryManager", "SubscribedContent-310093Enabled", value);
                    break;
                case "cb7":
                    Registry.SetValue("HKEY_CURRENT_USER\\" + cur_ver + "AdvertisingInfo", "Enabled", value);
                    break;
                case "cb8":
                    Registry.SetValue("HKEY_CURRENT_USER\\" + cur_ver + "Privacy", "TailoredExperiencesWithDiagnosticDataEnabled", value);
                    break;
                case "cb9":
                    Registry.SetValue("HKEY_CURRENT_USER\\" + cur_ver + "Explorer\\Advanced", "Start_IrisRecommendations", value);
                    break;
            }
            return true;
        }

        private void Checked(object sender, RoutedEventArgs e)
        {
            ToggleOptions(((CheckBox)sender).Name, true);
        }

        private void Unchecked(object sender, RoutedEventArgs e)
        {
            ToggleOptions(((CheckBox)sender).Name, false);
        }

        private void Closing_Window(object sender, System.ComponentModel.CancelEventArgs e)
        {
            MessageBox.Show("You May Need To Restart For Changes To Apply", "Twindows", MessageBoxButton.OK, MessageBoxImage.Information);
        }

        private void TextBlock_MouseEnter(object sender, MouseEventArgs e)
        {
            TextBlock textBlock = sender as TextBlock;
            textBlock.Foreground = new SolidColorBrush(Colors.IndianRed);
            HomeText.Text = "Twindows😈";
        }

        private void TextBlock_MouseLeave(object sender, MouseEventArgs e)
        {
            TextBlock textBlock = sender as TextBlock;
            textBlock.Foreground = new SolidColorBrush(Colors.White);
            HomeText.Text = "Twindows";
        }
    }
}
