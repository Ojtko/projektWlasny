   M S B A M L   `   `   `  ����  Dziennik    Dziennik.MainWindow   5   	   W SPresentationCore, Version=7.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35\ XPresentationFramework, Version=7.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35e aSystem.Windows.Controls.Ribbon, Version=7.0.0.0, Culture=neutral, PublicKeyToken=b77a5c561934e089R NWindowsBase, Version=7.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35F 9http://schemas.microsoft.com/winfx/2006/xaml/presentation     5      R NSystem.Xaml, Version=7.0.0.0, Culture=neutral, PublicKeyToken=b77a5c561934e089:x,http://schemas.microsoft.com/winfx/2006/xaml     5   	     � Title$  Dziennik��5   	   $	��450��6   $	��800��6'    � 	Resources 5         Styl �� 
TargetType �� Property �� Value 	 Styl2 	 Styl3��%e  &	        &	 m     &	 �     �� 5   
   " ��6   .�5      ��  � ��
 ��� �6+   �� 5       � ��$ 5q�6(   5	      �� 5
   
   " ��6   .�5      ��  � ��
 ��İ�6+   �� 5       � ��$ 5q�6(   5      �� 5   
   " ��6   .�5      ��  � ��
 �����6+   �� 5       � ��$ 5q�6(   5      5      .��5      ]� .+�5   
   o� $	��Top=�6   .@�5      m� $��_File��6   .@�5      m� -   5        $��_Exit��5      6*   5      m� 5      $��_Help��6   .@�5      m� -   5        $��_About��5      6+   5      5      �� 5   
   -   5        $��Dodaj ucznia��5      $	��Top=�6?   #��[  6T   �� 5   
   -   5        $��Edytuj ucznia��5      $	��Top=�6A   #��[ 6V   �� 5   
   -   5        $��Usuń ucznia��5      $	��Top=�6A   #��[ 6V   � 5"   
    � RowDefinitions 5#      �� 5$      $��* �6    �� 5%      $
��Auto �6    .+�5(      &   System.Windows.Controls.DataGrid  -   5          Name$ UczniowieDataGrid��5(         AutoGenerateColumns$ False��62      CanUserAddRows$ False��6N   	   SelectionMode$	 Single=�5)   9   ��6   �� *	Uczniowie+
   Columns
 5*      0  *System.Windows.Controls.DataGridTextColumn  5+      ,  &System.Windows.Controls.DataGridColumn   Header$ Imię��6)      Width5  /System.Windows.Controls.DataGridLengthConverter$ * 6P   1  +System.Windows.Controls.DataGridBoundColumn   Binding 67   �� *Imie+6P     5,      $ Nazwisko��6)   $ * 6X    6;   �� *
Nazwisko+6X     5-      $
 Opis��6)   $ * 6P    67   �� *Opis+6P     5.      $ Ocena��6)   $ * 6R    68   �� *Ocena+6R   50      �� 52      $��1��6   .@�53      �� .��54      �� $��Ready��6    55      56      57      58      59      