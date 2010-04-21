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
    internal class UnityFilter
    {
        private Project Project;

        public string Name;
        public string Path;

        public UnityFilter(Project project)
        {
            this.Project = project;

            this.Name = DefaultName;
            this.Path = DefaultPath;

            this.LoadSettings();
        }

        public VCFilter GetVCFilter()
        {
            try
            {
                VCProject vcproject = this.Project.Object as VCProject;
                foreach (VCFilter filter in vcproject.Filters as IVCCollection)
                {
                    if (filter.Parent == vcproject && filter.Name == this.Name)
                    {
                        return filter;
                    }
                }
            }
            catch { }
            return null;
        }

        public VCFilter AddVCFilter()
        {
            try
            {
                if (this.GetVCFilter() == null)
                {
                    VCProject vcproject = this.Project.Object as VCProject;
                    return vcproject.AddFilter(this.Name) as VCFilter;
                }
            }
            catch { }
            return null;
        }

        public void LoadSettings()
        {
            try
            {
                if (this.Project.Globals.get_VariableExists(NameKey))
                {
                    this.Name = this.Project.Globals[NameKey].ToString();
                }

                if (this.Project.Globals.get_VariableExists(PathKey))
                {
                    this.Path = this.Project.Globals[PathKey].ToString();
                }
            }
            catch (Exception ex)
            {
                Utils.ShowError("LoadSettings failed: " + ex.Message);
            }
        }

        public void SaveSettings()
        {
            try
            {
                this.Project.Globals.set_VariablePersists(NameKey, true);
                this.Project.Globals[NameKey] = this.Name;
                this.Project.Globals.set_VariablePersists(NameKey, true);

                this.Project.Globals.set_VariablePersists(PathKey, true);
                this.Project.Globals[PathKey] = this.Path;
                this.Project.Globals.set_VariablePersists(PathKey, true);

                this.AddVCFilter();
            }
            catch (Exception ex)
            {
                Utils.ShowError("SaveSettings failed: " + ex.Message);
            }
        }

        public const string DefaultName = "_Unity";
        public const string DefaultPath = "_Unity";

        public const string NameKey = "UnityFilterName";
        public const string PathKey = "UnityFilterPath";
    }
}
