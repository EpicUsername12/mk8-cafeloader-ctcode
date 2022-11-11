import os, hashlib, sys, subprocess, shutil, glob

RED = "[91m"
RESET = "[0m"
GREEN = "[92m"
BLUE = "[94m"
MAGENTA = "[95m"
YELLOW = "[93m"

print(BLUE + "The build script will default to building for console" + RESET)
print(GREEN + "python build.py " + MAGENTA + "<cemu|clean>" + RESET)
print()
print(MAGENTA + "Magenta " + RESET + "\t-> Optional")
print(RED + "Red " + RESET + "\t\t-> Error")
print(YELLOW + "Yellow " + RESET + "\t\t-> Warning")
print(GREEN + "Green " + RESET + "\t\t-> File or directory")
print(BLUE + "Blue " + RESET + "\t\t-> Indication")
print(RESET)

building_for_console = True
if (len(sys.argv) >= 2) and (sys.argv[1].lower() == "cemu"):
	building_for_console = False

if (len(sys.argv) >= 2) and (sys.argv[1].lower() == "clean"):
	if os.path.exists("project.gpj"): os.remove("project.gpj")
	if os.path.exists("files/Addr.bin"): os.remove("files/Addr.bin")
	if os.path.exists("files/Code.bin"): os.remove("files/Code.bin")
	if os.path.exists("files/Data.bin"): os.remove("files/Data.bin")
	if os.path.exists("files/Patches.hax"): os.remove("files/Patches.hax")
	if os.path.exists("files/Turbo.rpx"): os.remove("files/Turbo.rpx")
	if os.path.exists("build/project.ld"): os.remove("build/project.ld")
	
	shutil.rmtree("build/objs", ignore_errors=True)

	files = glob.glob("build/*.o")
	for file in files:
		os.remove(file)

	files = glob.glob("build/linker/game_*.x")
	for file in files:
		os.remove(file)

	print("Project cleaned!")
	exit()

# Check Turbo_ORIG exists
if not os.path.exists("files/Turbo_ORIG.rpx"):
	print(RED + "Please fetch the .RPX of the v64 update of Mario Kart 8 and put it in the " + GREEN + "files " + RED +"folder with the name " + GREEN + "Turbo_ORIG.rpx" + RESET)
	exit()

if not building_for_console:

	print(BLUE + "Building for: " + RESET + "CEMU Emulator")

	# Check Turbo_ORIG has the good signature
	turbo_orig = open("files/Turbo_ORIG.rpx", "rb")
	if hashlib.md5(turbo_orig.read()).hexdigest() != "1b8473fe24eeab27509923c78db51ec0":
		print(YELLOW + "Your Turbo_ORIG.rpx doesn't match the expected file signature.")
		print("This build script will still try to go through and continue as normal building but don't expect the built RPX to work." + RESET)

	subprocess.call("python build/scripts/compiler_cemu.py . MK8_ALL_Latest_Cemu files/Turbo_ORIG.rpx")

else:

	print(BLUE + "Building for: " + RESET + "Console")

	subprocess.call("python build/scripts/compiler.py . MK8_ALL_Latest")

"""
@echo off

if exist files/Turbo_ORIG.rpx (
	echo "whats good"
) else (
	echo [91mPlease fetch the .RPX of the v64 update of Mario Kart 8 and put it in the [92mfiles [91mfolder with the name [92mTurbo_ORIG.rpx[0m
	if %~1 == "cemu" (
		echo cemu
	) else (
		echo console
	)
)
"""