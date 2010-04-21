using System;
using System.IO;
using System.Text;
using System.Collections;
using System.Collections.Generic;
using System.Collections.Specialized;
using Extensibility;
using EnvDTE;
using EnvDTE80;
using Microsoft.VisualStudio.CommandBars;
using System.Resources;
using System.Reflection;
using System.Globalization;
using System.Diagnostics;
using Microsoft.VisualStudio.VCProjectEngine;
using System.Text.RegularExpressions;

namespace UnityBuild
{
    internal class UnityManager
    {
        public Project Project;
        public VCProject VCProject;
        public VCConfiguration VCConfig;

        public UnityFilter Filter;
        public Dictionary<string, Cpp> Cpps = new Dictionary<string, Cpp>();
        public Dictionary<string, Unity> Unities = new Dictionary<string, Unity>();

        public UnityManager(VCProject vcproject)
        {
            this.Project = vcproject.Object as Project;
            this.VCProject = vcproject;
            this.VCConfig = Connect.GetActiveVCConfig(this.VCProject);

            this.Filter = new UnityFilter(this.Project);
        }

        public void LoadUnities()
        {
            this.Unities = new Dictionary<string, Unity>();

            VCFilter unityfilter = this.Filter.GetVCFilter();
            if (unityfilter != null)
            {
                foreach (VCFile file in unityfilter.Files as IVCCollection)
                {
                    if (file.Extension.ToLower() == ".cpp")
                    {
                        Unity unity = new Unity(Path.GetFileNameWithoutExtension(file.Name));
                        unity.Load(file);
                        this.Unities.Add(unity.Name, unity);
                    }
                }
            }
        }

        public void LoadCpps()
        {
            this.Cpps = new Dictionary<string, Cpp>();

            string config = Connect.GetActiveConfigString(this.Project);

            VCFilter unityfilter = this.Filter.GetVCFilter();

            foreach (VCFile file in this.VCProject.Files as IVCCollection)
            {
                if (file.Extension.ToLower() == ".cpp" && file.Parent != unityfilter)
                {
                    VCFileConfiguration cfg = Connect.GetFileConfiguration(file, config);
                    VCCLCompilerTool vctool = cfg.Tool as VCCLCompilerTool;
                    if (vctool != null)
                    {
                        if (vctool.UsePrecompiledHeader == Microsoft.VisualStudio.VCProjectEngine.pchOption.pchCreateUsingSpecific)
                        {
                            continue;
                        }
                    }

                    Cpp cpp = this.GetCppInUnity(file.RelativePath);
                    if (cpp == null)
                    {
                        cpp = new Cpp(file);
                    }
                    this.Cpps.Add(cpp.Name, cpp);
                }
            }
        }

        public Cpp GetCppInUnity(string name)
        {
            Cpp cpp = null;
            foreach (Unity unity in this.Unities.Values)
            {
                if (unity.Cpps.TryGetValue(name, out cpp))
                {
                    break;
                }
            }
            return cpp;
        }

        public void SaveUnities()
        {
            try
            {
                VCFilter unityfilter = this.Filter.GetVCFilter();
                if (unityfilter == null)
                {
                    unityfilter = this.VCProject.AddFilter(this.Filter.Name) as VCFilter;
                }

                List<VCFile> oldfiles = new List<VCFile>();
                foreach (VCFile file in unityfilter.Files as IVCCollection)
                {
                    oldfiles.Add(file);
                }
                foreach (VCFile file in oldfiles)
                {
                    file.Remove();
                }

                IVCCollection tools = this.VCConfig.Tools as IVCCollection;
                VCCLCompilerTool vctool = tools.Item("VCCLCompilerTool") as VCCLCompilerTool;

                string pch = Connect.GetPCH(this.VCProject, this.VCConfig);

                foreach (Unity unity in this.Unities.Values)
                {
                    unity.Save(this.VCProject.ProjectDirectory, this.Filter.Path, pch);

                    VCFile file = unityfilter.AddFile(unity.FileName) as VCFile;

                    foreach (VCFileConfiguration fileconfig in file.FileConfigurations as IVCCollection)
                    {
                        vctool = fileconfig.Tool as VCCLCompilerTool;
                        if (vctool != null)
                        {
                            vctool.AdditionalIncludeDirectories = "\"$(ProjectDir)/\"";
                        }
                    }
                }
            }
            catch (System.Exception ex)
            {
                Utils.ShowError("SaveUnities failed: " + ex.Message);
            }
        }
    }
}
