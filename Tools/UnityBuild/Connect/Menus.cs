using System;
using Extensibility;
using EnvDTE;
using EnvDTE80;
using Microsoft.VisualStudio.CommandBars;
using System.Resources;
using System.Reflection;
using System.Globalization;
using System.Diagnostics;
using Microsoft.VisualStudio.VCProjectEngine;
using System.Collections.Generic;

namespace UnityBuild
{
    public partial class Connect
    {
        private readonly string MenuName = "Unity Build";

        private void InitMenus()
        {
            try
            {
                CommandBar menu;

                menu = this.CreateContextMenuItem(this.MenuName, "Solution");

                this.CreateMenuItem(menu, "Enable Unity", "Solution_EnableUnity");
                this.CreateMenuItem(menu, "Disable Unity", "Solution_DisableUnity");
                this.CreateMenuItem(menu, "Export Unity", "Solution_ExportUnity", true);
                this.CreateMenuItem(menu, "Import Unity", "Solution_ImportUnity");
                this.CreateMenuItem(menu, "Clone", "Solution_Clone", true);

                menu = this.CreateContextMenuItem(this.MenuName, "Project");

                this.CreateMenuItem(menu, "Unity ...", "Project_Unity");
                this.CreateMenuItem(menu, "Enable Unity", "Project_EnableUnity", true);
                this.CreateMenuItem(menu, "Disable Unity", "Project_DisableUnity");

                menu = this.CreateContextMenuItem(this.MenuName, "Folder");

                this.CreateMenuItem(menu, "Include Cpps", "Folder_Include");
                this.CreateMenuItem(menu, "Exclude Cpps", "Folder_Exclude");

                menu = this.CreateContextMenuItem(this.MenuName, "Item");

                this.CreateMenuItem(menu, "Include", "Item_Include");
                this.CreateMenuItem(menu, "Exclude", "Item_Exclude");
                this.CreateMenuItem(menu, "Remove From Unity", "Item_RemoveFromUnity", true);
            }
            catch { }
        }

        private void RemoveOldMenus()
        {
            try
            {
                //this.RemoveContextMenuItem("Build Helper", "Solution");
                //this.RemoveContextMenuItem("Clone", "Solution");
                //this.RemoveContextMenuItem("Include Batched Cpps", "Solution");
                //this.RemoveContextMenuItem("Exclude Batched Cpps", "Solution");

                //this.RemoveContextMenuItem("Build Helper", "Project");
                //this.RemoveContextMenuItem("Batch ...", "Project");
                //this.RemoveContextMenuItem("Include Batched Cpps", "Project");
                //this.RemoveContextMenuItem("Exclude Batched Cpps", "Project");

                //this.RemoveContextMenuItem("Build Helper", "Folder");
                //this.RemoveContextMenuItem("Include Cpps", "Folder");
                //this.RemoveContextMenuItem("Exclude Cpps", "Folder");

                //this.RemoveContextMenuItem("Build Helper", "Item");
                //this.RemoveContextMenuItem("Unbatch", "Item");
            }
            catch { }
        }

        #region Create

        private CommandBar CreateMainMenuItem(string name, string parentName)
        {
            try
            {
                try
                {
                    ResourceManager rm = new ResourceManager("UnityBuild.CommandBar", Assembly.GetExecutingAssembly());
                    CultureInfo culture = new System.Globalization.CultureInfo(this.DTE.LocaleID);
                    parentName = rm.GetString(culture.TwoLetterISOLanguageName + parentName);
                }
                catch { }

                CommandBar mainmenu = (this.DTE.CommandBars as CommandBars)["MenuBar"];
                CommandBarPopup parent = mainmenu.Controls[parentName] as CommandBarPopup;

                CommandBar item = null;
                foreach (CommandBarControl control in parent.Controls)
                {
                    if (control.Caption == name)
                    {
                        item = (control as CommandBarPopup).CommandBar;
                        break;
                    }
                }
                if (item == null)
                {
                    if (parent.Controls.Count > 0)
                    {
                        parent.Controls[1].BeginGroup = true;
                    }
                    item = this.DTE.Commands.AddCommandBar(name, EnvDTE.vsCommandBarType.vsCommandBarTypeMenu, parent.CommandBar, 1) as CommandBar;
                }

                return item;
            }
            catch
            {
                return null;
            }
        }

        private CommandBar CreateContextMenuItem(string name, string parentName)
        {
            try
            {
                CommandBar parent = (this.DTE.CommandBars as CommandBars)[parentName];

                CommandBar item = null;
                foreach (CommandBarControl control in parent.Controls)
                {
                    if (control.Caption == name)
                    {
                        item = (control as CommandBarPopup).CommandBar;
                        break;
                    }
                }
                if (item == null)
                {
                    if (parent.Controls.Count > 0)
                    {
                        parent.Controls[1].BeginGroup = true;
                    }
                    item = this.DTE.Commands.AddCommandBar(name, EnvDTE.vsCommandBarType.vsCommandBarTypeMenu, parent, 1) as CommandBar;
                }

                return item;
            }
            catch
            {
                return null;
            }
        }

        private void CreateMenuItem(CommandBar parent, string text, string name)
        {
            this.CreateMenuItem(parent, text, name, false);
        }

        private void CreateMenuItem(CommandBar parent, string text, string name, bool beginGroup)
        {
            if (parent == null) return;
            try
            {
                Command command = null;
                if (!this.Commands.TryGetValue(this.CommandNamePrefix + name, out command))
                {
                    //Add a command to the Commands collection:
                    object[] guids = new object[] { };
                    command = (this.DTE.Commands as Commands2).AddNamedCommand2(this.Instance, name, text, "", true, 0, ref guids, (int)vsCommandStatus.vsCommandStatusSupported | (int)vsCommandStatus.vsCommandStatusEnabled, (int)vsCommandStyle.vsCommandStylePictAndText, vsCommandControlType.vsCommandControlTypeButton);
                    this.Commands.Add(command.Name, command);
                }

                CommandBarControl item = null;

                // check id exists
                foreach (CommandBarControl control in parent.Controls)
                {
                    if (control.Caption == text)
                    {
                        item = control;
                        break;
                    }
                }

                if (item == null)
                {
                    //Add a control for the command to the menu:
                    item = command.AddControl(parent, parent.Controls.Count + 1) as CommandBarControl;
                }

                item.BeginGroup = beginGroup;
            }
            catch (Exception ex)
            {
                Utils.ShowError("CreateMenuItem failed: " + ex.Message);
            }
        }

        #endregion

        #region Remove

        private void RemoveMainMenuItem(string name, string parentName)
        {
            try
            {
                try
                {
                    ResourceManager rm = new ResourceManager("UnityBuild.CommandBar", Assembly.GetExecutingAssembly());
                    CultureInfo culture = new System.Globalization.CultureInfo(this.DTE.LocaleID);
                    parentName = rm.GetString(culture.TwoLetterISOLanguageName + parentName);
                }
                catch { }

                CommandBar mainmenu = (this.DTE.CommandBars as CommandBars)["MenuBar"];
                CommandBar parent = (mainmenu.Controls[parentName] as CommandBarPopup).CommandBar;
                this.RemoveMenuItem(name, parent);
            }
            catch { }
        }

        private void RemoveContextMenuItem(string name, string parentName)
        {
            try
            {
                CommandBar parent = (this.DTE.CommandBars as CommandBars)[parentName];
                this.RemoveMenuItem(name, parent);
            }
            catch { }
        }

        private void RemoveMenuItem(string name, CommandBar parent)
        {
            try
            {
                CommandBar item = null;
                foreach (CommandBarControl control in parent.Controls)
                {
                    if (control.Caption == name)
                    {
                        item = (control as CommandBarPopup).CommandBar;
                        break;
                    }
                }
                if (item != null)
                {
                    this.DTE.Commands.RemoveCommandBar(item);
                }
            }
            catch { }
        }

        #endregion
    }
}
