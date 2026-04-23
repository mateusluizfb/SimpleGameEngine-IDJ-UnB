# Top-level Makefile — detects the OS and delegates to the correct platform Makefile.
#
# Supported targets: all release debug clean package help
#
# On Linux, Makefile.win is also available for cross-compiling to Windows:
#   make PLATFORM=win <target>

# ---------------------------------------------------------------------------
# Platform detection
# ---------------------------------------------------------------------------
UNAME := $(shell uname -s)

ifeq ($(UNAME),Darwin)
  PLATFORM ?= macos
else ifeq ($(UNAME),Linux)
  PLATFORM ?= linux
else ifneq (,$(findstring MINGW,$(UNAME)))
  PLATFORM ?= win
else ifneq (,$(findstring MSYS,$(UNAME)))
  PLATFORM ?= win
else ifneq (,$(findstring CYGWIN,$(UNAME)))
  PLATFORM ?= win
else
  $(error Unsupported platform: $(UNAME). Set PLATFORM=macos|linux|win manually.)
endif

PLATFORM_MAKEFILE = Makefile.$(PLATFORM)

# ---------------------------------------------------------------------------
# Forwarding rules
# ---------------------------------------------------------------------------
.PHONY: all release debug clean package help

all release debug clean package help:
	$(MAKE) -f $(PLATFORM_MAKEFILE) $@
