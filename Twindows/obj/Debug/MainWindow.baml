   M S B A M L   `   `   `  ����C  ?Twindows, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null#clr-namespace:TwindowsTwindows  5   	       Twindows.MainWindow   5   	   R NWindowsBase, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35\ XPresentationFramework, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35W SPresentationCore, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35D 9http://schemas.microsoft.com/winfx/2006/xaml/presentation    5   	   R NSystem.Xaml, Version=4.0.0.0, Culture=neutral, PublicKeyToken=b77a5c561934e089:x,http://schemas.microsoft.com/winfx/2006/xaml     5   	   @d2http://schemas.microsoft.com/expression/blend/2008     5   	   Jmc;http://schemas.openxmlformats.org/markup-compatibility/2006     5   	   (localclr-namespace:Twindows     5   	   -   5          � 
ResizeMode$  NoResize=�5   	    � WindowStartupLocation$ CenterScreen=�5	   	   ���	#01FFFFFF � Title$ Twindows��5   	    � WindowStyle$
 None=�5   	    � AllowsTransparency . $	��240��5   	   $	��250��5   	   '  !System.Windows.Shell.WindowChrome   WindowChrome 5        5   
      CaptionHeight$ 30Q�5         CornerRadius$ 0��5         GlassFrameThickness$ 0q�5      	   UseAeroCaptionButtons	 .  5      
 � 	Resources
 5       �� MergedDictionaries �� Source�� 5   
    5      �� 5      $ 
theme.xaml?�6%   %    5      .��5!      �  � RowDefinitions 5"   
   �� 5#      $��44 �6   �� 5$      $
��Auto �6   .+�5&   
   � $��0��6   .+�5'      � .+�5(      �� -   5         ��Name$ HomeText��5(         IsHitTestVisibleInChrome . $��Twindows��6[    J� Opacity$	 0.8Q�6k   
�������$
��Bold"�6�   $��24(�6�   $��Italic$�6�    J� SnapsToDevicePixels .  K� ZIndex$ 1��6�   $��12,6,0,0q�6�   $	��Top=�6�   $
��Left=�6   � Cursor$
 Hand��61  5)   .   �� 5*      
�������$��12(�6.   $
��Left=�6<   $��Italic$�6W   $��Medium"�6j   $��Bottom=�6~    �� TextAlignment$
 Left=�6�   $��4,0,8,5q�6�   $
��v0.1��6�   5+      �� 5,      -   5        $	����5,      $��10(�6(   $ 1��66   $��40��6G   $��30��6`    . 6l   5-      � 5.   
   $��1��6   .+�5/      �� $��12,0,0,6q�6   .+�50      �� -   5         ��Name$	 cb1��50      $��Disable File Explorer Ads��6P   $��Italic$�6t   �� 51      -   5        $	 cb2��51      $&�� Disable Lock Screen Tips And Ads��6P   $��Italic$�6{   �� 52      -   5        $	 cb3��52      $��Disable Settings Ads��6P   $��Italic$�6o   �� 53      -   5        $	 cb4��53      $"��Disable General Tips And Ads��6P   $��Italic$�6w   �� 54      -   5        $	 cb5��54      $ ��Disable "Finish Setup" Ads��6P   $��Italic$�6   �� 55      -	   5        $	 cb6��55      $&�� Disable "Welcome Experience" Ads��6P   $��Italic$�6�   �� 56      -
   5        $	 cb7��56      $��Disable Personalized Ads��6P   $��Italic$�6s   �� 57      -   5        $	 cb8��57      $$��Disable "Tailored Experiences"��6P   $��Italic$�6�   �� 58      -   5        $	 cb9��58      $��Disable Start Menu Ads��6P   $��Italic$�6q   59      5:      5;      5=      