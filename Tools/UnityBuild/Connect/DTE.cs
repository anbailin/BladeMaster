using System;
using System.Collections.Generic;
using System.Text;
using EnvDTE;
using EnvDTE80;
using Microsoft.VisualStudio.VCProjectEngine;

namespace UnityBuild
{
    public partial class Connect
    {
        private bool Busy = false;

        private Project ActiveProject
        {
            get
            {
                Array projects = this.DTE.ActiveSolutionProjects as Array;
                if (projects.Length == 1)
                {
                    return projects.GetValue(0) as Project;
                }
                return null;
            }
        }

        private VCProject ActiveVCProject
        {
            get
            {
                Project project = this.ActiveProject;
                if (project != null && project.CodeModel.Language == CodeModelLanguageConstants.vsCMLanguageVC)
                {
                    return project.Object as VCProject;
                }
                return null;
            }
        }

        private ProjectItem SelectedItem
        {
            get
            {
                UIHierarchy explorer = this.DTE.Windows.Item(EnvDTE.Constants.vsWindowKindSolutionExplorer).Object as UIHierarchy;
                Array items = explorer.SelectedItems as Array;
                if (items.Length == 1)
                {
                    return (items.GetValue(0) as UIHierarchyItem).Object as ProjectItem;
                }
                return null;
            }
        }

        private List<ProjectItem> SelectedItems
        {
            get
            {
                UIHierarchy explorer = this.DTE.Windows.Item(EnvDTE.Constants.vsWindowKindSolutionExplorer).Object as UIHierarchy;

                List<ProjectItem> items = new List<ProjectItem>();
                foreach (object item in explorer.SelectedItems as Array)
                {
                    items.Add((item as UIHierarchyItem).Object as ProjectItem);
                }

                return items;
            }
        }

        private VCFilter SelectedVCFilter
        {
            get
            {
                ProjectItem item = this.SelectedItem;
                if (item != null && item.Kind.Equals(EnvDTE.Constants.vsProjectItemKindVirtualFolder))
                {
                    return item.Object as VCFilter;
                }
                return null;
            }
        }

        private VCFile SelectedCppFile
        {
            get
            {
                ProjectItem item = this.SelectedItem;
                if (item != null && item.Name.EndsWith(".cpp", true, null))
                {
                    return item.Object as VCFile;
                }
                return null;
            }
        }

        public static void SetExcludedFromBuild(VCFilter filter, string config, bool excluded)
        {
            foreach (VCFile file in filter.Files as IVCCollection)
            {
                if (file.Extension.ToLower() == ".cpp")
                {
                    Connect.SetExcludedFromBuild(file, config, excluded);
                }
            }
            foreach (VCFilter subfilter in filter.Filters as IVCCollection)
            {
                Connect.SetExcludedFromBuild(subfilter, config, excluded);
            }
        }

        public static void SetExcludedFromBuild(VCFile file, string config, bool excluded)
        {
            VCFileConfiguration cfg = Connect.GetFileConfiguration(file, config);
            if (cfg != null)
            {
                cfg.ExcludedFromBuild = excluded;
            }
        }

        public static Project GetProject(VCFile file)
        {
            return (file.project as VCProject).Object as Project;
        }

        public static Project GetProject(VCFilter filter)
        {
            return (filter.project as VCProject).Object as Project;
        }

        public static string GetActiveConfigString(Project project)
        {
            try
            {
                return project.ConfigurationManager.ActiveConfiguration.ConfigurationName + "|" + project.ConfigurationManager.ActiveConfiguration.PlatformName;
            }
            catch { }
            return "";
        }

        public static VCConfiguration GetActiveVCConfig(VCProject project)
        {
            try
            {
                string config = Connect.GetActiveConfigString(project.Object as Project);
                return (project.Configurations as IVCCollection).Item(config) as VCConfiguration;
            }
            catch { }
            return null;
        }

        public static VCConfiguration GetVCConfig(VCProject project, string config)
        {
            try
            {
                return (project.Configurations as IVCCollection).Item(config) as VCConfiguration;
            }
            catch { }
            return null;
        }

        public static VCFile GetVCFile(VCProject project, string name)
        {
            try
            {
                if (project != null)
                {
                    return (project.Files as IVCCollection).Item(name) as VCFile;
                }
            }
            catch { }
            return null;
        }

        public static VCFileConfiguration GetFileConfiguration(VCFile file, string config)
        {
            return (file.FileConfigurations as IVCCollection).Item(config) as VCFileConfiguration;
        }

        public static string GetVirtualPath(VCFile file)
        {
            try
            {
                string path = file.Name;

                VCFilter filter = file.Parent as VCFilter;
                if (filter != null)
                {
                    path = filter.CanonicalName + "\\" + path;
                }

                return path;
            }
            catch { }
            return "";
        }

        public static string GetPCH(VCProject project, VCConfiguration config)
        {
            string pch = "";

            IVCCollection tools = config.Tools as IVCCollection;
            VCCLCompilerTool vctool = tools.Item("VCCLCompilerTool") as VCCLCompilerTool;
            if (vctool != null)
            {
                pch = vctool.PrecompiledHeaderThrough;
            }

            if (pch != "")
            {
                VCFile file = Connect.GetVCFile(project, config.Evaluate(pch));
                if (file != null)
                {
                    pch = file.Name;
                }
            }

            return pch;
        }
    }
}
