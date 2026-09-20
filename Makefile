# Granada — mruby 4.0.0 + Nuklear v4.13.3
#
# mruby is cloned on demand into vendor/mruby (gitignored).
# Nuklear is vendored as vendor/nuklear/nuklear.h.

MRUBY_VERSION ?= 4.0.0
MRUBY_DIR     := vendor/mruby
MRUBY_CONFIG  := $(CURDIR)/build_config.rb
NUKLEAR_H     := vendor/nuklear/nuklear.h

export MRUBY_CONFIG

# mruby's Rakefile needs Ruby >= 2.7. macOS ships 2.6; prefer Homebrew Ruby.
HOMEBREW_RUBY := /opt/homebrew/opt/ruby/bin
ifneq ($(wildcard $(HOMEBREW_RUBY)/ruby),)
  export PATH := $(HOMEBREW_RUBY):$(PATH)
  RUBY := $(HOMEBREW_RUBY)/ruby
else
  RUBY ?= ruby
endif

.PHONY: all mruby test inventory hello kitchen clean distclean check-ruby

all: mruby

check-ruby:
	@$(RUBY) -e 'abort("Ruby >= 2.7 required to build mruby, got #{RUBY_VERSION}") if Gem::Version.new(RUBY_VERSION) < Gem::Version.new("2.7")'
	@echo "build ruby: $(RUBY) ($$($(RUBY) -v))"

$(MRUBY_DIR)/.git:
	git clone --depth 1 --branch $(MRUBY_VERSION) https://github.com/mruby/mruby.git $(MRUBY_DIR)

mruby: check-ruby $(NUKLEAR_H) $(MRUBY_DIR)/.git
	$(MAKE) -C $(MRUBY_DIR)

test: mruby
	$(MAKE) -C $(MRUBY_DIR) test

inventory: $(NUKLEAR_H)
	ruby tools/inventory_nuklear.rb

hello: mruby
	$(MRUBY_DIR)/bin/mruby examples/hello.rb

kitchen: mruby
	$(MRUBY_DIR)/bin/mruby examples/kitchen_sink.rb

clean:
	@if [ -d $(MRUBY_DIR) ]; then $(MAKE) -C $(MRUBY_DIR) clean; fi

distclean:
	rm -rf $(MRUBY_DIR)
