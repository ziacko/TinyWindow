using Sharpmake;
using System.Collections.Generic;

namespace tinywindow
{
    [Sharpmake.Generate]
    public class ExampleProject : Project
    {
        public ExampleProject()
        {
            Name = "Example";

            if (Util.GetExecutingPlatform() == Platform.linux)
            {
                AddTargets(new Target(
                    Platform.linux,
                    DevEnv.make,
                    Optimization.Debug | Optimization.Release
                ));
            }

            else if (Util.GetExecutingPlatform() == Platform.win64)
            {
                AddTargets(new Target(
                    Platform.win64,
                    DevEnv.vs2022,
                    Optimization.Debug | Optimization.Release
                ));
            }
            SourceRootPath = @"[project.SharpmakeCsPath]\Example\";

            var excludedFolders = new List<string>();
            excludedFolders.Add("CMake.*");
            SourceFilesExcludeRegex.Add(@"\.*\\(" + string.Join("|", excludedFolders.ToArray()) + @")\\");
        }

        [Configure()]
        public void ConfigureAll(Configuration conf, Target target)
        {
            conf.ProjectFileName = "[project.Name]";
            conf.ProjectPath = @"[project.SharpmakeCsPath]\generated\projects";
            conf.IncludePaths.Add(@"[project.SharpmakeCsPath]\Include\");
            conf.IncludePaths.Add(@"[project.SharpmakeCsPath]\Dependencies\");
            conf.IncludePaths.Add(@"[project.SharpmakeCsPath]\Examples\dependencies\");
            conf.TargetPath = @"[project.SharpmakeCsPath]\bin";
            
            if (Util.GetExecutingPlatform() == Platform.linux)
            {
                conf.Options.Add(Sharpmake.Options.Makefile.Compiler.CppLanguageStandard.Cpp2a);
                conf.Options.Add(Sharpmake.Options.Makefile.General.PlatformToolset.Clang);
                
                conf.AdditionalLinkerOptions.Add(@"-GL");
                conf.AdditionalLinkerOptions.Add(@"-lX11");                
				conf.AdditionalLinkerOptions.Add(@"-lXinerama");
				conf.AdditionalLinkerOptions.Add(@"-lXrandr");
            }

            else if (Util.GetExecutingPlatform() == Platform.win64)
            {
                conf.Options.Add(Sharpmake.Options.Vc.General.WindowsTargetPlatformVersion.Latest);
            }
        }

        public virtual void AddSources()
        {
            SourceFiles.Add(@"[project.SharpmakeCsPath]\Include\TinyWindow.h");
        }
    }

    [Sharpmake.Generate]
    public class TinyWindowSolution : Sharpmake.Solution
    {
        public TinyWindowSolution()
        {
            Name = "TinyWindow";

            if (Util.GetExecutingPlatform() == Platform.linux)
            {
                AddTargets(new Target(
                    Platform.linux,
                    DevEnv.make,
                    Optimization.Debug | Optimization.Release
                ));
            }

            else if (Util.GetExecutingPlatform() == Platform.win64)
            {
                AddTargets(new Target(
                    Platform.win64,
                    DevEnv.vs2022,
                    Optimization.Debug | Optimization.Release
                ));
            }
        }

        [Configure()]
        public void ConfigureAll(Configuration conf, Target target)
        {
            conf.SolutionFileName = "[solution.Name]";
            conf.SolutionPath = @"[solution.SharpmakeCsPath]";
            conf.AddProject<ExampleProject>(target);
        }
 
        [Sharpmake.Main]
        public static void SharpmakeMain(Sharpmake.Arguments arguments)
        {
            arguments.Generate<TinyWindowSolution>();
        }
    }
}