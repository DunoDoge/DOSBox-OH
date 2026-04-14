cmake_minimum_required(VERSION 3.5.0)
project(OHDosBox)

set(NATIVERENDER_ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR})
set(DOSBOX_SRC ${CMAKE_CURRENT_SOURCE_DIR}/dosbox-src/src)

if(DEFINED PACKAGE_FIND_FILE)
    include(${PACKAGE_FIND_FILE})
endif()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)

set(DOSBOX_COMMON_SOURCES
    ${DOSBOX_SRC}/dosbox.cpp

    ${DOSBOX_SRC}/config/config.cpp
    ${DOSBOX_SRC}/config/setup.cpp

    ${DOSBOX_SRC}/cpu/callback.cpp
    ${DOSBOX_SRC}/cpu/core_normal.cpp
    ${DOSBOX_SRC}/cpu/core_simple.cpp
    ${DOSBOX_SRC}/cpu/core_full.cpp
    ${DOSBOX_SRC}/cpu/core_prefetch.cpp
    ${DOSBOX_SRC}/cpu/cpu.cpp
    ${DOSBOX_SRC}/cpu/flags.cpp
    ${DOSBOX_SRC}/cpu/modrm.cpp
    ${DOSBOX_SRC}/cpu/mmx.cpp
    ${DOSBOX_SRC}/cpu/paging.cpp

    ${DOSBOX_SRC}/fpu/fpu.cpp

    ${DOSBOX_SRC}/hardware/memory.cpp
    ${DOSBOX_SRC}/hardware/pic.cpp
    ${DOSBOX_SRC}/hardware/timer.cpp
    ${DOSBOX_SRC}/hardware/port.cpp
    ${DOSBOX_SRC}/hardware/dma.cpp
    ${DOSBOX_SRC}/hardware/cmos.cpp
    ${DOSBOX_SRC}/hardware/pci_bus.cpp
    ${DOSBOX_SRC}/hardware/ide.cpp
    ${DOSBOX_SRC}/hardware/virtualbox.cpp
    ${DOSBOX_SRC}/hardware/vmware.cpp

    ${DOSBOX_SRC}/hardware/video/vga.cpp
    ${DOSBOX_SRC}/hardware/video/vga_draw.cpp
    ${DOSBOX_SRC}/hardware/video/vga_gfx.cpp
    ${DOSBOX_SRC}/hardware/video/vga_seq.cpp
    ${DOSBOX_SRC}/hardware/video/vga_attr.cpp
    ${DOSBOX_SRC}/hardware/video/vga_crtc.cpp
    ${DOSBOX_SRC}/hardware/video/vga_dac.cpp
    ${DOSBOX_SRC}/hardware/video/vga_misc.cpp
    ${DOSBOX_SRC}/hardware/video/vga_other.cpp
    ${DOSBOX_SRC}/hardware/video/vga_memory.cpp
    ${DOSBOX_SRC}/hardware/video/vga_s3.cpp
    ${DOSBOX_SRC}/hardware/video/vga_tseng.cpp
    ${DOSBOX_SRC}/hardware/video/vga_xga.cpp
    ${DOSBOX_SRC}/hardware/video/vga_paradise.cpp
    ${DOSBOX_SRC}/hardware/video/voodoo.cpp
    ${DOSBOX_SRC}/hardware/video/reelmagic/driver.cpp
    ${DOSBOX_SRC}/hardware/video/reelmagic/player.cpp
    ${DOSBOX_SRC}/hardware/video/reelmagic/video_mixer.cpp

    ${DOSBOX_SRC}/hardware/input/keyboard.cpp
    ${DOSBOX_SRC}/hardware/input/keyboard_scancodes.cpp
    ${DOSBOX_SRC}/hardware/input/mouse.cpp
    ${DOSBOX_SRC}/hardware/input/mouse_common.cpp
    ${DOSBOX_SRC}/hardware/input/mouse_config.cpp
    ${DOSBOX_SRC}/hardware/input/mouse_interfaces.cpp
    ${DOSBOX_SRC}/hardware/input/mouse_manymouse.cpp
    ${DOSBOX_SRC}/hardware/input/mouseif_dos_driver.cpp
    ${DOSBOX_SRC}/hardware/input/mouseif_dos_driver_state.cpp
    ${DOSBOX_SRC}/hardware/input/mouseif_ps2_bios.cpp
    ${DOSBOX_SRC}/hardware/input/mouseif_virtual_machines.cpp
    ${DOSBOX_SRC}/hardware/input/joystick.cpp
    ${DOSBOX_SRC}/hardware/input/intel8042.cpp
    ${DOSBOX_SRC}/hardware/input/intel8255.cpp

    ${DOSBOX_SRC}/hardware/audio/opl.cpp
    ${DOSBOX_SRC}/hardware/audio/pcspeaker.cpp
    ${DOSBOX_SRC}/hardware/audio/pcspeaker_discrete.cpp
    ${DOSBOX_SRC}/hardware/audio/pcspeaker_impulse.cpp
    ${DOSBOX_SRC}/hardware/audio/soundblaster.cpp
    ${DOSBOX_SRC}/hardware/audio/speaker.cpp
    ${DOSBOX_SRC}/hardware/audio/adlib_gold.cpp
    ${DOSBOX_SRC}/hardware/audio/cms.cpp
    ${DOSBOX_SRC}/hardware/audio/covox.cpp
    ${DOSBOX_SRC}/hardware/audio/disney.cpp
    ${DOSBOX_SRC}/hardware/audio/gus.cpp
    ${DOSBOX_SRC}/hardware/audio/imfc.cpp
    ${DOSBOX_SRC}/hardware/audio/innovation.cpp
    ${DOSBOX_SRC}/hardware/audio/lpt_dac.cpp
    ${DOSBOX_SRC}/hardware/audio/mpu401.cpp
    ${DOSBOX_SRC}/hardware/audio/ps1audio.cpp
    ${DOSBOX_SRC}/hardware/audio/ston1_dac.cpp
    ${DOSBOX_SRC}/hardware/audio/tandy_sound.cpp
    ${DOSBOX_SRC}/hardware/audio/mame/saa1099.cpp
    ${DOSBOX_SRC}/hardware/audio/mame/sn76496.cpp

    ${DOSBOX_SRC}/hardware/serialport/serialport.cpp
    ${DOSBOX_SRC}/hardware/serialport/misc_util.cpp
    ${DOSBOX_SRC}/hardware/serialport/nullmodem.cpp
    ${DOSBOX_SRC}/hardware/serialport/serialdummy.cpp
    ${DOSBOX_SRC}/hardware/serialport/serialmouse.cpp
    ${DOSBOX_SRC}/hardware/serialport/softmodem.cpp

    ${DOSBOX_SRC}/hardware/network/ipx.cpp
    ${DOSBOX_SRC}/hardware/network/ipxserver.cpp
    ${DOSBOX_SRC}/hardware/network/ne2000.cpp

    ${DOSBOX_SRC}/ints/bios.cpp
    ${DOSBOX_SRC}/ints/bios_disk.cpp
    ${DOSBOX_SRC}/ints/bios_keyboard.cpp
    ${DOSBOX_SRC}/ints/bios_pci.cpp
    ${DOSBOX_SRC}/ints/ems.cpp
    ${DOSBOX_SRC}/ints/xms.cpp
    ${DOSBOX_SRC}/ints/int10.cpp
    ${DOSBOX_SRC}/ints/int10_char.cpp
    ${DOSBOX_SRC}/ints/int10_memory.cpp
    ${DOSBOX_SRC}/ints/int10_misc.cpp
    ${DOSBOX_SRC}/ints/int10_modes.cpp
    ${DOSBOX_SRC}/ints/int10_pal.cpp
    ${DOSBOX_SRC}/ints/int10_put_pixel.cpp
    ${DOSBOX_SRC}/ints/int10_vesa.cpp
    ${DOSBOX_SRC}/ints/int10_video_state.cpp
    ${DOSBOX_SRC}/ints/int10_vptable.cpp

    ${DOSBOX_SRC}/dos/dos.cpp
    ${DOSBOX_SRC}/dos/dos_classes.cpp
    ${DOSBOX_SRC}/dos/dos_code_page.cpp
    ${DOSBOX_SRC}/dos/dos_devices.cpp
    ${DOSBOX_SRC}/dos/dos_execute.cpp
    ${DOSBOX_SRC}/dos/dos_files.cpp
    ${DOSBOX_SRC}/dos/dos_ioctl.cpp
    ${DOSBOX_SRC}/dos/dos_keyboard_layout.cpp
    ${DOSBOX_SRC}/dos/dos_locale.cpp
    ${DOSBOX_SRC}/dos/dos_locale_data.cpp
    ${DOSBOX_SRC}/dos/dos_memory.cpp
    ${DOSBOX_SRC}/dos/dos_misc.cpp
    ${DOSBOX_SRC}/dos/dos_mscdex.cpp
    ${DOSBOX_SRC}/dos/dos_programs.cpp
    ${DOSBOX_SRC}/dos/dos_tables.cpp
    ${DOSBOX_SRC}/dos/dos_windows.cpp
    ${DOSBOX_SRC}/dos/drive_cache.cpp
    ${DOSBOX_SRC}/dos/drive_fat.cpp
    ${DOSBOX_SRC}/dos/drive_iso.cpp
    ${DOSBOX_SRC}/dos/drive_local.cpp
    ${DOSBOX_SRC}/dos/drive_overlay.cpp
    ${DOSBOX_SRC}/dos/drive_virtual.cpp
    ${DOSBOX_SRC}/dos/drives.cpp
    ${DOSBOX_SRC}/dos/cdrom.cpp
    ${DOSBOX_SRC}/dos/cdrom_image.cpp
    ${DOSBOX_SRC}/dos/cdrom_ioctl_linux.cpp
    ${DOSBOX_SRC}/dos/programs.cpp

    ${DOSBOX_SRC}/dos/programs/attrib.cpp
    ${DOSBOX_SRC}/dos/programs/autotype.cpp
    ${DOSBOX_SRC}/dos/programs/biostest.cpp
    ${DOSBOX_SRC}/dos/programs/boot.cpp
    ${DOSBOX_SRC}/dos/programs/choice.cpp
    ${DOSBOX_SRC}/dos/programs/clip.cpp
    ${DOSBOX_SRC}/dos/programs/help.cpp
    ${DOSBOX_SRC}/dos/programs/intro.cpp
    ${DOSBOX_SRC}/dos/programs/keyb.cpp
    ${DOSBOX_SRC}/dos/programs/loadfix.cpp
    ${DOSBOX_SRC}/dos/programs/loadrom.cpp
    ${DOSBOX_SRC}/dos/programs/ls.cpp
    ${DOSBOX_SRC}/dos/programs/makeimg.cpp
    ${DOSBOX_SRC}/dos/programs/mem.cpp
    ${DOSBOX_SRC}/dos/programs/mixer.cpp
    ${DOSBOX_SRC}/dos/programs/mode.cpp
    ${DOSBOX_SRC}/dos/programs/more.cpp
    ${DOSBOX_SRC}/dos/programs/more_output.cpp
    ${DOSBOX_SRC}/dos/programs/mount.cpp
    ${DOSBOX_SRC}/dos/programs/mount_common.cpp
    ${DOSBOX_SRC}/dos/programs/mouse.cpp
    ${DOSBOX_SRC}/dos/programs/mousectl.cpp
    ${DOSBOX_SRC}/dos/programs/move.cpp
    ${DOSBOX_SRC}/dos/programs/rescan.cpp
    ${DOSBOX_SRC}/dos/programs/serial.cpp
    ${DOSBOX_SRC}/dos/programs/setver.cpp
    ${DOSBOX_SRC}/dos/programs/showpic.cpp
    ${DOSBOX_SRC}/dos/programs/subst.cpp
    ${DOSBOX_SRC}/dos/programs/tree.cpp

    ${DOSBOX_SRC}/shell/shell.cpp
    ${DOSBOX_SRC}/shell/shell_batch.cpp
    ${DOSBOX_SRC}/shell/shell_cmds.cpp
    ${DOSBOX_SRC}/shell/shell_history.cpp
    ${DOSBOX_SRC}/shell/shell_misc.cpp
    ${DOSBOX_SRC}/shell/autoexec.cpp
    ${DOSBOX_SRC}/shell/command_line.cpp
    ${DOSBOX_SRC}/shell/file_reader.cpp

    ${DOSBOX_SRC}/gui/sdl_gui.cpp
    ${DOSBOX_SRC}/gui/mapper.cpp
    ${DOSBOX_SRC}/gui/clipboard.cpp
    ${DOSBOX_SRC}/gui/titlebar.cpp
    ${DOSBOX_SRC}/gui/render/render.cpp
    ${DOSBOX_SRC}/gui/render/sdl_renderer.cpp
    ${DOSBOX_SRC}/gui/render/opengl_renderer.cpp
    ${DOSBOX_SRC}/gui/render/deinterlacer.cpp
    ${DOSBOX_SRC}/gui/render/scaler/scalers.cpp
    ${DOSBOX_SRC}/gui/render/auto_image_adjustments.cpp
    ${DOSBOX_SRC}/gui/render/auto_shader_switcher.cpp
    ${DOSBOX_SRC}/gui/render/shader.cpp
    ${DOSBOX_SRC}/gui/render/shader_manager.cpp
    ${DOSBOX_SRC}/gui/render/shader_pipeline.cpp

    ${DOSBOX_SRC}/audio/mixer.cpp
    ${DOSBOX_SRC}/audio/disk_noise.cpp
    ${DOSBOX_SRC}/audio/compressor.cpp
    ${DOSBOX_SRC}/audio/envelope.cpp
    ${DOSBOX_SRC}/audio/noise_gate.cpp
    ${DOSBOX_SRC}/audio/opl_capture.cpp
    ${DOSBOX_SRC}/audio/clap/event_list.cpp
    ${DOSBOX_SRC}/audio/clap/library.cpp
    ${DOSBOX_SRC}/audio/clap/plugin.cpp
    ${DOSBOX_SRC}/audio/clap/plugin_manager.cpp

    ${DOSBOX_SRC}/midi/midi.cpp
    ${DOSBOX_SRC}/midi/mt32.cpp
    ${DOSBOX_SRC}/midi/mt32_lasynth_model.cpp
    ${DOSBOX_SRC}/midi/fluidsynth.cpp
    ${DOSBOX_SRC}/midi/soundcanvas.cpp

    ${DOSBOX_SRC}/capture/capture.cpp
    ${DOSBOX_SRC}/capture/capture_audio.cpp
    ${DOSBOX_SRC}/capture/capture_midi.cpp
    ${DOSBOX_SRC}/capture/capture_video.cpp
    ${DOSBOX_SRC}/capture/image/image_capturer.cpp
    ${DOSBOX_SRC}/capture/image/image_saver.cpp
    ${DOSBOX_SRC}/capture/image/image_scaler.cpp
    ${DOSBOX_SRC}/capture/image/png_writer.cpp

    ${DOSBOX_SRC}/network/ethernet.cpp
    ${DOSBOX_SRC}/network/ethernet_slirp.cpp

    ${DOSBOX_SRC}/webserver/bridge.cpp
    ${DOSBOX_SRC}/webserver/webserver.cpp
    ${DOSBOX_SRC}/webserver/cpu.cpp
    ${DOSBOX_SRC}/webserver/memory.cpp
    ${DOSBOX_SRC}/webserver/dos.cpp

    ${DOSBOX_SRC}/misc/support.cpp
    ${DOSBOX_SRC}/misc/cross.cpp
    ${DOSBOX_SRC}/misc/messages.cpp
    ${DOSBOX_SRC}/misc/video.cpp
    ${DOSBOX_SRC}/misc/dos_rwops.cpp
    ${DOSBOX_SRC}/misc/fs_utils.cpp
    ${DOSBOX_SRC}/misc/fs_utils_posix.cpp
    ${DOSBOX_SRC}/misc/unicode.cpp
    ${DOSBOX_SRC}/misc/unicode_encodings.cpp
    ${DOSBOX_SRC}/misc/console.cpp
    ${DOSBOX_SRC}/misc/ansi_code_markup.cpp
    ${DOSBOX_SRC}/misc/help_util.cpp
    ${DOSBOX_SRC}/misc/host_locale.cpp
    ${DOSBOX_SRC}/misc/host_locale_posix.cpp
    ${DOSBOX_SRC}/misc/image_decoder.cpp
    ${DOSBOX_SRC}/misc/iso_locale_codes.cpp
    ${DOSBOX_SRC}/misc/messages_adjust.cpp
    ${DOSBOX_SRC}/misc/messages_po_entry.cpp
    ${DOSBOX_SRC}/misc/rwqueue.cpp

    ${DOSBOX_SRC}/utils/env_utils.cpp
    ${DOSBOX_SRC}/utils/string_utils.cpp

    ${DOSBOX_SRC}/hardware/port_containers.cpp
)

set(DOSBOX_LIB_SOURCES
    ${DOSBOX_SRC}/libs/decoders/SDL_sound.c
    ${DOSBOX_SRC}/libs/decoders/flac.c
    ${DOSBOX_SRC}/libs/decoders/mp3_seek_table.cpp
    ${DOSBOX_SRC}/libs/decoders/mp3.cpp
    ${DOSBOX_SRC}/libs/decoders/opus.cpp
    ${DOSBOX_SRC}/libs/decoders/vorbis.c
    ${DOSBOX_SRC}/libs/decoders/wav.c

    ${DOSBOX_SRC}/libs/loguru/loguru.cpp

    ${DOSBOX_SRC}/libs/ESFMu/esfm.c
    ${DOSBOX_SRC}/libs/ESFMu/esfm_registers.c

    ${DOSBOX_SRC}/libs/nuked/opl3.c

    ${DOSBOX_SRC}/libs/residfp/Dac.cpp
    ${DOSBOX_SRC}/libs/residfp/EnvelopeGenerator.cpp
    ${DOSBOX_SRC}/libs/residfp/ExternalFilter.cpp
    ${DOSBOX_SRC}/libs/residfp/Filter.cpp
    ${DOSBOX_SRC}/libs/residfp/Filter6581.cpp
    ${DOSBOX_SRC}/libs/residfp/Filter8580.cpp
    ${DOSBOX_SRC}/libs/residfp/FilterModelConfig.cpp
    ${DOSBOX_SRC}/libs/residfp/FilterModelConfig6581.cpp
    ${DOSBOX_SRC}/libs/residfp/FilterModelConfig8580.cpp
    ${DOSBOX_SRC}/libs/residfp/Integrator6581.cpp
    ${DOSBOX_SRC}/libs/residfp/Integrator8580.cpp
    ${DOSBOX_SRC}/libs/residfp/OpAmp.cpp
    ${DOSBOX_SRC}/libs/residfp/SID.cpp
    ${DOSBOX_SRC}/libs/residfp/Spline.cpp
    ${DOSBOX_SRC}/libs/residfp/WaveformCalculator.cpp
    ${DOSBOX_SRC}/libs/residfp/WaveformGenerator.cpp
    ${DOSBOX_SRC}/libs/residfp/version.cc
    ${DOSBOX_SRC}/libs/residfp/resample/SincResampler.cpp

    ${DOSBOX_SRC}/libs/whereami/whereami.c
    ${DOSBOX_SRC}/libs/YM7128B_emu/YM7128B_emu.c
    ${DOSBOX_SRC}/libs/riffcpp/membuffer.cpp
    ${DOSBOX_SRC}/libs/riffcpp/riffcpp.cpp
    ${DOSBOX_SRC}/libs/tal-chorus/Lfo.cpp
    ${DOSBOX_SRC}/libs/zmbv/zmbv.cpp
    ${DOSBOX_SRC}/libs/glad/release/src/gl.c
)

set(PLATFORM_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/platform/sdl_ohos_video.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/platform/sdl_ohos_timer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/platform/sdl_ohos_thread.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/platform/sdl_ohos_events.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/platform/sdl_ohos_stubs.cpp
)

set(BRIDGE_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/dosbox_bridge.cpp
)

configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/dosbox_config_ohos.h
    ${CMAKE_CURRENT_BINARY_DIR}/dosbox_config.h
)

add_library(entry SHARED
    napi_init.cpp
    dosbox_main_wrapper.cpp
    ${BRIDGE_SOURCES}
    ${PLATFORM_SOURCES}
    ${DOSBOX_COMMON_SOURCES}
    ${DOSBOX_LIB_SOURCES}
)

target_include_directories(entry PRIVATE
    ${NATIVERENDER_ROOT_PATH}
    ${NATIVERENDER_ROOT_PATH}/platform
    ${DOSBOX_SRC}
    ${DOSBOX_SRC}/libs
    ${DOSBOX_SRC}/libs/decoders
    ${DOSBOX_SRC}/libs/residfp
    ${DOSBOX_SRC}/libs/ESFMu
    ${DOSBOX_SRC}/libs/nuked
    ${DOSBOX_SRC}/libs/loguru
    ${DOSBOX_SRC}/libs/riffcpp
    ${DOSBOX_SRC}/libs/tal-chorus
    ${DOSBOX_SRC}/libs/zmbv
    ${DOSBOX_SRC}/libs/YM7128B_emu
    ${DOSBOX_SRC}/libs/whereami
    ${DOSBOX_SRC}/libs/glad/release/include
    ${DOSBOX_SRC}/libs/http
    ${DOSBOX_SRC}/libs/json
    ${DOSBOX_SRC}/libs/simpleini
    ${DOSBOX_SRC}/libs/stb_truetype
    ${DOSBOX_SRC}/libs/base64
    ${DOSBOX_SRC}/libs/clap
    ${DOSBOX_SRC}/libs/mverb
    ${DOSBOX_SRC}/libs/PL_MPEG
    ${DOSBOX_SRC}/libs/include
    ${DOSBOX_SRC}/libs/manymouse
    ${DOSBOX_SRC}/libs/enet/include
    ${CMAKE_CURRENT_BINARY_DIR}
)

target_compile_definitions(entry PRIVATE
    OHOS_PLATFORM
    entry_EXPORTS
)

target_compile_options(entry PRIVATE
    -Wno-unknown-warning-option
    -Wno-unknown-pragmas
    -Wno-conversion
    -Wno-narrowing
    -Wno-unused-parameter
    -Wno-unused-function
    -Wno-sign-compare
    -Wno-missing-field-initializers
    -Wno-deprecated
    -Wno-extra-semi
    -fpermissive
)

target_link_libraries(entry PUBLIC
    libace_napi.z.so
    libace_ndk.z.so
    libnative_window.so
    libhilog_ndk.z.so
)
