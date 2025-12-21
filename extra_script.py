Import("env")
import os

# Find the correct objcopy tool - look for it in the platform's toolchain
platform = env.PioPlatform()
toolchain_prefix = "xtensa-esp32-elf-"

# Get objcopy from the toolchain bin directory
objcopy_tool = os.path.join(
    platform.get_package_dir("toolchain-xtensa-esp32"),
    "bin",
    toolchain_prefix + "objcopy"
)

print(f"Using objcopy: {objcopy_tool}")

# Custom HEX from ELF
env.AddPostAction(
    "$BUILD_DIR/${PROGNAME}.elf",
    env.VerboseAction(" ".join([
        f'"{objcopy_tool}"', "-O", "ihex", "-R", ".eeprom",
        "$BUILD_DIR/${PROGNAME}.elf", "$BUILD_DIR/${PROGNAME}.hex"
    ]), "Building $BUILD_DIR/${PROGNAME}.hex")
)
