using System;
using System.Collections.Generic;
using System.Text;
using EnvDTE;
using EnvDTE80;
using System.Windows.Forms;
using System.IO;
using System.Xml;
using Microsoft.VisualStudio.VCProjectEngine;

namespace UnityBuild
{
    public partial class Connect
    {
        private readonly string CommandNamePrefix = "UnityBuild.Connect.";

        private Dictionary<string, Command> Commands = new Dictionary<string, Command>();
        private Dictionary<string, Executer> Executers = new Dictionary<string, Executer>();

        private void InitCommands()
        {
            this.Commands.Clear();
            this.Executers.Clear();

            foreach (Command command in this.DTE.Commands as Commands2)
            {
                if (command.Name.StartsWith(this.CommandNamePrefix))
                {
                    this.Commands.Add(command.Name, command);
                }
            }

            this.Executers["Solution_Clone"] = new Executer(this.Solution_Clone);
            this.Executers["Solution_DisableUnity"] = new Executer(this.Solution_DisableUnity);
            this.Executers["Solution_EnableUnity"] = new Executer(this.Solution_EnableUnity);
            this.Executers["Solution_ExportUnity"] = new Executer(this.Solution_ExportUnity);
            this.Executers["Solution_ImportUnity"] = new Executer(this.Solution_ImportUnity);

            this.Executers["Project_Unity"] = new Executer(this.Project_Unity);
            this.Executers["Project_DisableUnity"] = new Executer(this.Project_DisableUnity);
            this.Executers["Project_EnableUnity"] = new Executer(this.Project_EnableUnity);

            this.Executers["Folder_Include"] = new Executer(this.Folder_Include);
            this.Executers["Folder_Exclude"] = new Executer(this.Folder_Exclude);

            this.Executers["Item_Include"] = new Executer(this.Item_Include);
            this.Executers["Item_Exclude"] = new Executer(this.Item_Exclude);
            this.Executers["Item_RemoveFromUnity"] = new Executer(this.Item_RemoveFromUnity);
        }

        private void UpdateCommandStatus(string name, ref vsCommandStatus status)
        {
            if (!this.Executers.ContainsKey(name))
            {
                status = vsCommandStatus.vsCommandStatusUnsupported;
                return;
            }

            status = vsCommandStatus.vsCommandStatusSupported;

            if (this.Busy) return;
            if (this.DTE.Solution.SolutionBuild.BuildState == vsBuildState.vsBuildStateInProgress) return;

            switch (name)
            {
                case "Solution_Clone":
                case "Solution_DisableUnity":
                case "Solution_EnableUnity":
                case "Solution_ExportUnity":
                case "Solution_ImportUnity":
                {
                    status |= vsCommandStatus.vsCommandStatusEnabled;
                    break;
                }
                case "Project_Unity":
                case "Project_DisableUnity":
                case "Project_EnableUnity":
                {
                    if (this.ActiveVCProject != null)
                    {
                        status |= vsCommandStatus.vsCommandStatusEnabled;
                    }
                    else
                    {
                        status = vsCommandStatus.vsCommandStatusUnsupported;
                    }
                    break;
                }
                case "Folder_Include":
                case "Folder_Exclude":
                {
                    if (this.SelectedVCFilter != null)
                    {
                        status |= vsCommandStatus.vsCommandStatusEnabled;
                    }
                    else
                    {
                        status = vsCommandStatus.vsCommandStatusUnsupported;
                    }
                    break;
                }
                case "Item_Include":
                case "Item_Exclude":
                case "Item_RemoveFromUnity":
                {
                    if (this.SelectedCppFile != null)
                    {
                        status |= vsCommandStatus.vsCommandStatusEnabled;
                    }
                    else
                    {
                        status = vsCommandStatus.vsCommandStatusUnsupported;
                    }
                    break;
                }
            }
        }

        private void ExecuteCommand(string command)
        {
            this.Busy = true;
            try
            {
                if (this.Executers.ContainsKey(command))
                {
                    this.Executers[command]();
                }
            }
            catch (Exception ex)
            {
                Utils.ShowError(command + " failed: " + ex.Message);
            }
            this.Busy = false;
        }

        private void Solution_ExportUnity()
        {
            SaveFileDialog dialog = new SaveFileDialog();
            dialog.AddExtension = true;
            dialog.CheckPathExists = true;
            dialog.CreatePrompt = false;
            dialog.OverwritePrompt = true;
            dialog.DefaultExt = ".xml";
            dialog.Filter = "xml files | *.xml";
            dialog.FileName = "unity.xml";
            dialog.Title = "Export Unity";
            dialog.InitialDirectory = Utils.GetDirectoryPath(this.DTE.Solution.FileName);

            if (dialog.ShowDialog() != DialogResult.OK) return;

            try
            {
                XmlDocument xDoc = new XmlDocument();

                XmlElement xSolution = Utils.AddXmlElement(xDoc, "Solution");
                Utils.AddXmlAttribute(xSolution, "Path", this.DTE.Solution.FileName);

                foreach (Project project in this.DTE.Solution.Projects)
                {
                    if (project != null && project.CodeModel != null && project.CodeModel.Language == CodeModelLanguageConstants.vsCMLanguageVC)
                    {
                        this.Project_ExportUnity(project.Object as VCProject, xSolution);
                    }
                }

                xDoc.Save(dialog.FileName);

                Utils.ShowMessage("Export unity succeeded.");
            }
            catch (Exception ex)
            {
                Utils.ShowError("Export unity failed: " + ex.Message);
            }
        }

        private void Project_ExportUnity(VCProject project, XmlElement xParent)
        {
            if (project == null) return;

            UnityManager um = new UnityManager(project);
            um.LoadUnities();

            VCFilter unityfilter = um.Filter.GetVCFilter();
            if (unityfilter == null || um.Unities.Count == 0) return;

            XmlElement xProject = Utils.AddXmlElement(xParent, "Project");
            Utils.AddXmlAttribute(xProject, "Name", project.Name);
            Utils.AddXmlAttribute(xProject, "Path", project.ProjectFile);
            Utils.AddXmlAttribute(xProject, "UnityFilterName", um.Filter.Name);
            Utils.AddXmlAttribute(xProject, "UnityFilterPath", um.Filter.Path);

            foreach (Unity unity in um.Unities.Values)
            {
                XmlElement xUnity = Utils.AddXmlElement(xProject, "Unity");
                Utils.AddXmlAttribute(xUnity, "Name", unity.Name);

                foreach (Cpp cpp in unity.Cpps.Values)
                {
                    XmlElement xCpp = Utils.AddXmlElement(xUnity, "Cpp");
                    Utils.AddXmlAttribute(xCpp, "Name", cpp.Name);
                    Utils.AddXmlAttribute(xCpp, "Condition", cpp.Condition);
                }
            }
        }

        private void Solution_ImportUnity()
        {
            OpenFileDialog dialog = new OpenFileDialog();
            dialog.AddExtension = true;
            dialog.CheckFileExists = true;
            dialog.CheckPathExists = true;
            dialog.DefaultExt = ".xml";
            dialog.Filter = "xml files | *.xml";
            dialog.FileName = "unity.xml";
            dialog.Title = "Import Unity";
            dialog.InitialDirectory = Utils.GetDirectoryPath(this.DTE.Solution.FileName);

            if (dialog.ShowDialog() != DialogResult.OK) return;

            try
            {
                XmlDocument xDoc = new XmlDocument();
                xDoc.Load(dialog.FileName);

                if (xDoc.DocumentElement.Name != "Solution")
                {
                    throw new Exception("Invalid xml file format!");
                }

                XmlElement xSolution = xDoc.DocumentElement;

                foreach (Project project in this.DTE.Solution.Projects)
                {
                    if (project != null && project.CodeModel != null && project.CodeModel.Language == CodeModelLanguageConstants.vsCMLanguageVC)
                    {
                        XmlNode xProject = xSolution.SelectSingleNode(String.Format("Project[@Name='{0}']", project.Name));
                        if (xProject != null)
                        {
                            this.Project_ImportUnity(project.Object as VCProject, xProject);
                        }
                    }
                }

                Utils.ShowMessage("Import unity succeeded.");
            }
            catch (Exception ex)
            {
                Utils.ShowError("Import unity failed: " + ex.Message);
            }
        }

        private void Project_ImportUnity(VCProject project, XmlNode xProject)
        {
            if (project == null) return;

            UnityManager um = new UnityManager(project);

            um.Filter.Name = xProject.Attributes["UnityFilterName"].Value;
            um.Filter.Path = xProject.Attributes["UnityFilterPath"].Value;
            um.Filter.SaveSettings();

            um.Unities = new Dictionary<string, Unity>();

            foreach (XmlNode xUnity in xProject.ChildNodes)
            {
                if (xUnity.Name != "Unity")
                {
                    throw new Exception("Invalid xml file format!");
                }

                Unity unity = new Unity(xUnity.Attributes["Name"].Value);
                um.Unities.Add(unity.Name, unity);

                foreach (XmlNode xCpp in xUnity.ChildNodes)
                {
                    if (xCpp.Name != "Cpp")
                    {
                        throw new Exception("Invalid xml file format!");
                    }

                    Cpp cpp = new Cpp(xCpp.Attributes["Name"].Value);
                    cpp.Condition = xCpp.Attributes["Condition"].Value;
                    unity.Cpps.Add(cpp.Name, cpp);
                }
            }

            um.SaveUnities();
        }

        private void Solution_Clone()
        {
            string suffix = "";
            if (InputBox.Show("Solution Clone", "Enter the suffix to be added to each solution and project file:", ref suffix) == DialogResult.OK)
            {
                if (suffix.IndexOfAny(Path.GetInvalidFileNameChars()) != -1)
                {
                    Utils.ShowWarning("Illegal character in suffix.");
                    return;
                }

                foreach (Project project in this.DTE.Solution.Projects)
                {
                    Solution_Clone(project, suffix);
                }

                this.DTE.Solution.SaveAs(Utils.AddSuffixToFileName(this.DTE.Solution.FileName, suffix));
            }
        }

        private void Solution_Clone(Project project, string suffix)
        {
            if (project == null) return;

            if (project.Kind == ProjectKinds.vsProjectKindSolutionFolder)
            {
                foreach (ProjectItem item in project.ProjectItems)
                {
                    this.Solution_Clone(item.Object as Project, suffix);
                }
            }
            else
            {
                project.SaveAs(Utils.AddSuffixToFileName(project.FileName, suffix));
            }
        }

        private void Solution_DisableUnity()
        {
            foreach (Project project in this.DTE.Solution.Projects)
            {
                this.Solution_EnableUnity(project, false);
            }
        }

        private void Solution_EnableUnity()
        {
            foreach (Project project in this.DTE.Solution.Projects)
            {
                this.Solution_EnableUnity(project, true);
            }
        }

        private void Solution_EnableUnity(Project project, bool excluded)
        {
            if (project == null) return;

            if (project.Kind == ProjectKinds.vsProjectKindSolutionFolder)
            {
                foreach (ProjectItem item in project.ProjectItems)
                {
                    this.Solution_EnableUnity(item.Object as Project, excluded);
                }
            }
            else if (project.CodeModel != null && project.CodeModel.Language == CodeModelLanguageConstants.vsCMLanguageVC)
            {
                this.Project_EnableUnity(project.Object as VCProject, excluded);
            }
        }

        private void Project_Unity()
        {
            if (this.ActiveVCProject == null) return;

            UnityForm form = new UnityForm(this.ActiveVCProject);
            form.Show();
        }

        private void Project_DisableUnity()
        {
            this.Project_EnableUnity(this.ActiveVCProject, false);
        }

        private void Project_EnableUnity()
        {
            this.Project_EnableUnity(this.ActiveVCProject, true);
        }

        private void Project_EnableUnity(VCProject project, bool excluded)
        {
            if (project == null) return;

            string config = Connect.GetActiveConfigString(project.Object as Project);

            UnityManager um = new UnityManager(project);
            um.LoadUnities();

            VCFilter unityfilter = um.Filter.GetVCFilter();
            if (unityfilter == null || um.Unities.Count == 0) return;

            foreach (VCFile file in project.Files as IVCCollection)
            {
                if (file.Extension.ToLower() == ".cpp")
                {
                    if (file.Parent == unityfilter)
                    {
                        Connect.SetExcludedFromBuild(file, config, !excluded);
                    }
                    else
                    {
                        Connect.SetExcludedFromBuild(file, config, excluded && (um.GetCppInUnity(file.RelativePath) != null));
                    }
                }
            }
        }

        private void Folder_Include()
        {
            if (this.SelectedVCFilter == null) return;
            Connect.SetExcludedFromBuild(this.SelectedVCFilter, Connect.GetActiveConfigString(Connect.GetProject(this.SelectedVCFilter)), false);
        }

        private void Folder_Exclude()
        {
            if (this.SelectedVCFilter == null) return;
            Connect.SetExcludedFromBuild(this.SelectedVCFilter, Connect.GetActiveConfigString(Connect.GetProject(this.SelectedVCFilter)), true);
        }

        private void Item_Include()
        {
            if (this.SelectedCppFile == null) return;
            Connect.SetExcludedFromBuild(this.SelectedCppFile, Connect.GetActiveConfigString(Connect.GetProject(this.SelectedCppFile)), false);
        }

        private void Item_Exclude()
        {
            if (this.SelectedCppFile == null) return;
            Connect.SetExcludedFromBuild(this.SelectedCppFile, Connect.GetActiveConfigString(Connect.GetProject(this.SelectedCppFile)), true);
        }

        private void Item_RemoveFromUnity()
        {
            if (this.SelectedCppFile == null) return;

            UnityManager um = new UnityManager(this.ActiveVCProject);
            um.LoadUnities();

            Cpp cpp = um.GetCppInUnity(this.SelectedCppFile.RelativePath);
            if (cpp != null)
            {
                cpp.Unity.Cpps.Remove(cpp.Name);
                cpp.Unity.Save(this.ActiveVCProject.ProjectDirectory, um.Filter.Path, Connect.GetPCH(um.VCProject, um.VCConfig));

                Connect.SetExcludedFromBuild(this.SelectedCppFile, Connect.GetActiveConfigString(Connect.GetProject(this.SelectedCppFile)), false);
            }
        }
    }

    internal delegate void Executer();
}
