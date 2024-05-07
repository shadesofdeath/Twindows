using Microsoft.Win32;
using SophiApp.Helpers;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Globalization;
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
            HashSet<string> supportedLanguages = new HashSet<string>()
            {
                "de-DE", // (Deutsch)
                "en-US", // (English)
                "es-ES", // (Español)
                "fr-FR", // (Français)
                "it-IT", // (Italiano)
                "ja-JP", // (日本語)
                "ko-KR", // (한국어)
                "pt-PT", // (Português)
                "ru-RU", // (Русский)
                "tr-TR", // (Türkçe)
                "zh-CN"  // (简体中文)
            };

            // Windows'un mevcut dilini al
            CultureInfo currentCulture = CultureInfo.CurrentCulture;

            // Eğer dil destekleniyorsa, o dili kullan
            if (supportedLanguages.Contains(currentCulture.Name))
            {
                I18n.Instance.ApplyLanguage(currentCulture);
            }
            else
            {
                I18n.Instance.ApplyLanguage(new CultureInfo("en-US"));
            }
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


        private void InitializeKeys()
        {
            Dictionary<CheckBox, List<Tuple<RegistryHive, string, string, int>>> checks = new Dictionary<CheckBox, List<Tuple<RegistryHive, string, string, int>>>()
            {
                { FileExplorerAds, new List<Tuple<RegistryHive, string, string, int>>()
                    {
                        Tuple.Create(RegistryHive.CurrentUser, @"SOFTWARE\Microsoft\Windows\CurrentVersion\Explorer\Advanced", "ShowSyncProviderNotifications", 0)
                    }
                },
                { LockscreenAds, new List<Tuple<RegistryHive, string, string, int>>()
                    {
                        Tuple.Create(RegistryHive.CurrentUser, @"Software\Microsoft\Windows\CurrentVersion\ContentDeliveryManager", "RotatingLockScreenOverlayEnabled", 0),
                        Tuple.Create(RegistryHive.CurrentUser, @"Software\Microsoft\Windows\CurrentVersion\ContentDeliveryManager", "SubscribedContent-338387Enabled", 0)
                    }
                },
                { SettingsAds, new List<Tuple<RegistryHive, string, string, int>>()
                    {
                        Tuple.Create(RegistryHive.CurrentUser, @"Software\Microsoft\Windows\CurrentVersion\ContentDeliveryManager", "SubscribedContent-338393Enabled", 0),
                        Tuple.Create(RegistryHive.CurrentUser, @"Software\Microsoft\Windows\CurrentVersion\ContentDeliveryManager", "SubscribedContent-353694Enabled", 0),
                        Tuple.Create(RegistryHive.CurrentUser, @"Software\Microsoft\Windows\CurrentVersion\ContentDeliveryManager", "SubscribedContent-353696Enabled", 0)
                    }
                },
                { GeneralTips, new List<Tuple<RegistryHive, string, string, int>>()
                    {
                        Tuple.Create(RegistryHive.CurrentUser, @"Software\Microsoft\Windows\CurrentVersion\ContentDeliveryManager", "SubscribedContent-338389Enabled", 0)
                    }
                },
                { FinishSetupAds, new List<Tuple<RegistryHive, string, string, int>>()
                    {
                        Tuple.Create(RegistryHive.CurrentUser, @"Software\Microsoft\Windows\CurrentVersion\UserProfileEngagement", "ScoobeSystemSettingEnabled", 0)
                    }
                },
                { WelcomeExperienceAds, new List<Tuple<RegistryHive, string, string, int>>()
                    {
                        Tuple.Create(RegistryHive.CurrentUser, @"Software\Microsoft\Windows\CurrentVersion\ContentDeliveryManager", "SubscribedContent-310093Enabled", 0)
                    }
                },
                { PersonalizedAds, new List<Tuple<RegistryHive, string, string, int>>()
                    {
                        Tuple.Create(RegistryHive.CurrentUser, @"Software\Microsoft\Windows\CurrentVersion\AdvertisingInfo", "Enabled", 0)
                    }
                },
                { TailoredExperiences, new List<Tuple<RegistryHive, string, string, int>>()
                    {
                        Tuple.Create(RegistryHive.CurrentUser, @"Software\Microsoft\Windows\CurrentVersion\Privacy", "TailoredExperiencesWithDiagnosticDataEnabled", 0)
                    }
                },
                { StartMenuAds, new List<Tuple<RegistryHive, string, string, int>>()
                    {
                        Tuple.Create(RegistryHive.CurrentUser, @"Software\Microsoft\Windows\CurrentVersion\Explorer\Advanced", "Start_IrisRecommendations", 0)
                    }
                },
                { WebSearch, new List<Tuple<RegistryHive, string, string, int>>()
                    {
                        Tuple.Create(RegistryHive.CurrentUser, @"Software\Policies\Microsoft\Windows\Explorer", "DisableSearchBoxSuggestions", 1),
                        Tuple.Create(RegistryHive.CurrentUser, @"SOFTWARE\Microsoft\Windows\CurrentVersion\Search", "BingSearchEnabled", 0)
                    }
                },
                { Copilot, new List<Tuple<RegistryHive, string, string, int>>()
                    {
                        Tuple.Create(RegistryHive.CurrentUser, @"Software\Policies\Microsoft\Windows\WindowsCopilot", "TurnOffWindowsCopilot", 1),
                        Tuple.Create(RegistryHive.LocalMachine, @"SOFTWARE\Policies\Microsoft\Windows\WindowsCopilot", "TurnOffWindowsCopilot", 1),
                        Tuple.Create(RegistryHive.LocalMachine, @"SOFTWARE\Policies\Microsoft\Edge", "HubsSidebarEnabled", 0),
                        Tuple.Create(RegistryHive.CurrentUser, @"Software\Policies\Microsoft\Windows\Explorer", "DisableSearchBoxSuggestions", 1),
                        Tuple.Create(RegistryHive.LocalMachine, @"SOFTWARE\Policies\Microsoft\Windows\Explorer", "DisableSearchBoxSuggestions", 1)

                    }
                }
            };

            foreach (var item in checks)
            {
                bool isChecked = true;
                foreach (var check in item.Value)
                {
                    int? regValue = RegHelper.GetNullableIntValue(check.Item1, check.Item2, check.Item3);
                    if (!regValue.HasValue || regValue != check.Item4)
                    {
                        isChecked = false;
                        break;
                    }
                }
                item.Key.IsChecked = isChecked;
            }
        }

        // Disable Copilot
        private void Copilot_Checked(object sender, RoutedEventArgs e)
        {
            RegHelper.SetValue(RegistryHive.CurrentUser, @"Software\Policies\Microsoft\Windows\WindowsCopilot", "TurnOffWindowsCopilot", 1, RegistryValueKind.DWord);
            RegHelper.SetValue(RegistryHive.LocalMachine, @"SOFTWARE\Policies\Microsoft\Windows\WindowsCopilot", "TurnOffWindowsCopilot", 1, RegistryValueKind.DWord);
            RegHelper.SetValue(RegistryHive.LocalMachine, @"SOFTWARE\Policies\Microsoft\Edge", "HubsSidebarEnabled", 0, RegistryValueKind.DWord);
            RegHelper.SetValue(RegistryHive.CurrentUser, @"Software\Policies\Microsoft\Windows\Explorer", "DisableSearchBoxSuggestions", 1, RegistryValueKind.DWord);
            RegHelper.SetValue(RegistryHive.LocalMachine, @"SOFTWARE\Policies\Microsoft\Windows\Explorer", "DisableSearchBoxSuggestions", 1, RegistryValueKind.DWord);
        }

        private void Copilot_Unchecked(object sender, RoutedEventArgs e)
        {
            RegHelper.SetValue(RegistryHive.CurrentUser, @"Software\Policies\Microsoft\Windows\WindowsCopilot", "TurnOffWindowsCopilot", 0, RegistryValueKind.DWord);
            RegHelper.SetValue(RegistryHive.LocalMachine, @"SOFTWARE\Policies\Microsoft\Windows\WindowsCopilot", "TurnOffWindowsCopilot", 0, RegistryValueKind.DWord);
            RegHelper.SetValue(RegistryHive.LocalMachine, @"SOFTWARE\Policies\Microsoft\Edge", "HubsSidebarEnabled", 1, RegistryValueKind.DWord);
            RegHelper.SetValue(RegistryHive.CurrentUser, @"Software\Policies\Microsoft\Windows\Explorer", "DisableSearchBoxSuggestions", 0, RegistryValueKind.DWord);
            RegHelper.SetValue(RegistryHive.LocalMachine, @"SOFTWARE\Policies\Microsoft\Windows\Explorer", "DisableSearchBoxSuggestions", 0, RegistryValueKind.DWord);
        }

        // Disable Web Search
        private void WebSearch_Checked(object sender, RoutedEventArgs e)
        {
            RegHelper.SetValue(RegistryHive.CurrentUser, @"Software\Policies\Microsoft\Windows\Explorer", "DisableSearchBoxSuggestions", 1, RegistryValueKind.DWord);
            RegHelper.SetValue(RegistryHive.CurrentUser, @"SOFTWARE\Microsoft\Windows\CurrentVersion\Search", "BingSearchEnabled", 0, RegistryValueKind.DWord);

        }

        private void WebSearch_Unchecked(object sender, RoutedEventArgs e)
        {
            RegHelper.SetValue(RegistryHive.CurrentUser, @"Software\Policies\Microsoft\Windows\Explorer", "DisableSearchBoxSuggestions", 0, RegistryValueKind.DWord);
            RegHelper.SetValue(RegistryHive.CurrentUser, @"SOFTWARE\Microsoft\Windows\CurrentVersion\Search", "BingSearchEnabled", 1, RegistryValueKind.DWord);
        }

        // Turn off “Show suggestions for tips, shortcuts, new apps and more” in Start
        private void StartMenuAds_Checked(object sender, RoutedEventArgs e)
        {
            RegHelper.SetValue(RegistryHive.CurrentUser, @"Software\Microsoft\Windows\CurrentVersion\Explorer\Advanced", "Start_IrisRecommendations", 0, RegistryValueKind.DWord);
        }

        private void StartMenuAds_Unchecked(object sender, RoutedEventArgs e)
        {
            RegHelper.SetValue(RegistryHive.CurrentUser, @"Software\Microsoft\Windows\CurrentVersion\Explorer\Advanced", "Start_IrisRecommendations", 1, RegistryValueKind.DWord);
        }

        // Disable Tailored Experiences
        private void TailoredExperiences_Checked(object sender, RoutedEventArgs e)
        {
            RegHelper.SetValue(RegistryHive.CurrentUser, @"Software\Microsoft\Windows\CurrentVersion\Privacy", "TailoredExperiencesWithDiagnosticDataEnabled", 0, RegistryValueKind.DWord);
        }

        private void TailoredExperiences_Unchecked(object sender, RoutedEventArgs e)
        {
            RegHelper.SetValue(RegistryHive.CurrentUser, @"Software\Microsoft\Windows\CurrentVersion\Privacy", "TailoredExperiencesWithDiagnosticDataEnabled", 1, RegistryValueKind.DWord);
        }

        // Disable Advertising ID for Personalized Ads
        private void PersonalizedAds_Checked(object sender, RoutedEventArgs e)
        {
            RegHelper.SetValue(RegistryHive.CurrentUser, @"Software\Microsoft\Windows\CurrentVersion\AdvertisingInfo", "Enabled", 0, RegistryValueKind.DWord);
        }

        private void PersonalizedAds_Unchecked(object sender, RoutedEventArgs e)
        {
            RegHelper.SetValue(RegistryHive.CurrentUser, @"Software\Microsoft\Windows\CurrentVersion\AdvertisingInfo", "Enabled", 1, RegistryValueKind.DWord);
        }

        // Disable Welcome Experience Ads
        private void WelcomeExperienceAds_Checked(object sender, RoutedEventArgs e)
        {
            RegHelper.SetValue(RegistryHive.CurrentUser, @"Software\Microsoft\Windows\CurrentVersion\ContentDeliveryManager", "SubscribedContent-310093Enabled", 0, RegistryValueKind.DWord);
        }

        private void WelcomeExperienceAds_Unchecked(object sender, RoutedEventArgs e)
        {
            RegHelper.SetValue(RegistryHive.CurrentUser, @"Software\Microsoft\Windows\CurrentVersion\ContentDeliveryManager", "SubscribedContent-310093Enabled", 1, RegistryValueKind.DWord);
        }

        // Disable Finish Setup Ads
        private void FinishSetupAds_Checked(object sender, RoutedEventArgs e)
        {
            RegHelper.SetValue(RegistryHive.CurrentUser, @"Software\Microsoft\Windows\CurrentVersion\UserProfileEngagement", "ScoobeSystemSettingEnabled", 0, RegistryValueKind.DWord);
        }

        private void FinishSetupAds_Unchecked(object sender, RoutedEventArgs e)
        {
            RegHelper.SetValue(RegistryHive.CurrentUser, @"Software\Microsoft\Windows\CurrentVersion\UserProfileEngagement", "ScoobeSystemSettingEnabled", 1, RegistryValueKind.DWord);
        }

        // Disable General Tips And Ads
        private void GeneralTips_Checked(object sender, RoutedEventArgs e)
        {
            RegHelper.SetValue(RegistryHive.CurrentUser, @"Software\Microsoft\Windows\CurrentVersion\ContentDeliveryManager", "SubscribedContent-338389Enabled", 0, RegistryValueKind.DWord);
        }

        private void GeneralTips_Unchecked(object sender, RoutedEventArgs e)
        {
            RegHelper.SetValue(RegistryHive.CurrentUser, @"Software\Microsoft\Windows\CurrentVersion\ContentDeliveryManager", "SubscribedContent-338389Enabled", 1, RegistryValueKind.DWord);
        }

        // Disable Settings Ads
        private void SettingsAds_Checked(object sender, RoutedEventArgs e)
        {
            RegHelper.SetValue(RegistryHive.CurrentUser, @"Software\Microsoft\Windows\CurrentVersion\ContentDeliveryManager", "SubscribedContent-338393Enabled", 0, RegistryValueKind.DWord);
            RegHelper.SetValue(RegistryHive.CurrentUser, @"Software\Microsoft\Windows\CurrentVersion\ContentDeliveryManager", "SubscribedContent-353694Enabled", 0, RegistryValueKind.DWord);
            RegHelper.SetValue(RegistryHive.CurrentUser, @"Software\Microsoft\Windows\CurrentVersion\ContentDeliveryManager", "SubscribedContent-353696Enabled", 0, RegistryValueKind.DWord);
        }

        private void SettingsAds_Unchecked(object sender, RoutedEventArgs e)
        {
            RegHelper.SetValue(RegistryHive.CurrentUser, @"Software\Microsoft\Windows\CurrentVersion\ContentDeliveryManager", "SubscribedContent-338393Enabled", 1, RegistryValueKind.DWord);
            RegHelper.SetValue(RegistryHive.CurrentUser, @"Software\Microsoft\Windows\CurrentVersion\ContentDeliveryManager", "SubscribedContent-353694Enabled", 1, RegistryValueKind.DWord);
            RegHelper.SetValue(RegistryHive.CurrentUser, @"Software\Microsoft\Windows\CurrentVersion\ContentDeliveryManager", "SubscribedContent-353696Enabled", 1, RegistryValueKind.DWord);
        }

        // Disable Lock Screen Tips And Ads
        private void LockscreenAds_Checked(object sender, RoutedEventArgs e)
        {
            RegHelper.SetValue(RegistryHive.CurrentUser, @"Software\Microsoft\Windows\CurrentVersion\ContentDeliveryManager", "RotatingLockScreenOverlayEnabled", 0, RegistryValueKind.DWord);
            RegHelper.SetValue(RegistryHive.CurrentUser, @"Software\Microsoft\Windows\CurrentVersion\ContentDeliveryManager", "SubscribedContent-338387Enabled", 0, RegistryValueKind.DWord);
        }

        private void LockscreenAds_Unchecked(object sender, RoutedEventArgs e)
        {
            RegHelper.SetValue(RegistryHive.CurrentUser, @"Software\Microsoft\Windows\CurrentVersion\ContentDeliveryManager", "RotatingLockScreenOverlayEnabled", 1, RegistryValueKind.DWord);
            RegHelper.SetValue(RegistryHive.CurrentUser, @"Software\Microsoft\Windows\CurrentVersion\ContentDeliveryManager", "SubscribedContent-338387Enabled", 1, RegistryValueKind.DWord);
        }

        // Disable File Explorer Ads
        private void FileExplorerAds_Checked(object sender, RoutedEventArgs e)
        {
            RegHelper.SetValue(RegistryHive.CurrentUser, @"SOFTWARE\Microsoft\Windows\CurrentVersion\Explorer\Advanced", "ShowSyncProviderNotifications", 0, RegistryValueKind.DWord);
        }

        private void FileExplorerAds_Unchecked(object sender, RoutedEventArgs e)
        {
            RegHelper.SetValue(RegistryHive.CurrentUser, @"SOFTWARE\Microsoft\Windows\CurrentVersion\Explorer\Advanced", "ShowSyncProviderNotifications", 1, RegistryValueKind.DWord);
        }


        private void Close(object sender, RoutedEventArgs e)
        {
            try
            {
                Close();
            }
            catch { }
        }

        private void Github(object sender, MouseButtonEventArgs e)
        {
            try
            {
                Process.Start("https://github.com/shadesofdeath");
            }
            catch { }
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
