am__is_gnu_make = test -n '$(MAKEFILE_LIST)' && test -n '$(MAKELEVEL)'
am__make_running_with_option = \
  case $${target_option-} in \
      ?) ;; \
      *) echo "am__make_running_with_option: internal error: invalid" \
              "target option '$${target_option-}' specified" >&2; \
         exit 1;; \
  esac; \
  has_opt=no; \
  sane_makeflags=$$MAKEFLAGS; \
  if $(am__is_gnu_make); then \
    sane_makeflags=$$MFLAGS; \
  else \
    case $$MAKEFLAGS in \
      *\\[\ \	]*) \
        bs=\\; \
        sane_makeflags=`printf '%s\n' "$$MAKEFLAGS" \
          | sed "s/$$bs$$bs[$$bs $$bs	]*//g"`;; \
    esac; \
  fi; \
  skip_next=no; \
  strip_trailopt () \
  { \
    flg=`printf '%s\n' "$$flg" | sed "s/$$1.*$$//"`; \
  }; \
  for flg in $$sane_makeflags; do \
    test $$skip_next = yes && { skip_next=no; continue; }; \
    case $$flg in \
      *=*|--*) continue;; \
        -*I) strip_trailopt 'I'; skip_next=yes;; \
      -*I?*) strip_trailopt 'I';; \
        -*O) strip_trailopt 'O'; skip_next=yes;; \
      -*O?*) strip_trailopt 'O';; \
        -*l) strip_trailopt 'l'; skip_next=yes;; \
      -*l?*) strip_trailopt 'l';; \
      -[dEDm]) skip_next=yes;; \
      -[JT]) skip_next=yes;; \
    esac; \
    case $$flg in \
      *$$target_option*) has_opt=yes; break;; \
    esac; \
  done; \
  test $$has_opt = yes
am__make_dryrun = (target_option=n; $(am__make_running_with_option))
am__make_keepgoing = (target_option=k; $(am__make_running_with_option))
pkgdatadir = $(datadir)/libmemcached
pkgincludedir = $(includedir)/libmemcached
pkglibdir = $(libdir)/libmemcached
pkglibexecdir = $(libexecdir)/libmemcached
am__cd = CDPATH="$${ZSH_VERSION+.}$(PATH_SEPARATOR)" && cd
install_sh_DATA = $(install_sh) -c -m 644
install_sh_PROGRAM = $(install_sh) -c
install_sh_SCRIPT = $(install_sh) -c
INSTALL_HEADER = $(INSTALL_DATA)
transform = $(program_transform_name)
NORMAL_INSTALL = :
PRE_INSTALL = :
POST_INSTALL = :
NORMAL_UNINSTALL = :
PRE_UNINSTALL = :
POST_UNINSTALL = :
build_triplet = x86_64-unknown-linux-gnu
host_triplet = x86_64-unknown-linux-gnu
TESTS = $(bin_PROGRAMS) $(check_PROGRAMS)
XFAIL_TESTS = $(bin_PROGRAMS)
bin_PROGRAMS = $(am__EXEEXT_1) $(am__EXEEXT_2)
noinst_PROGRAMS = $(am__EXEEXT_3) $(am__EXEEXT_4) $(am__EXEEXT_10) \
	$(am__EXEEXT_6) $(am__EXEEXT_11) $(am__EXEEXT_12) \
	$(am__EXEEXT_13) $(am__EXEEXT_8) $(am__EXEEXT_14)
check_PROGRAMS = $(am__EXEEXT_3) $(am__EXEEXT_4) $(am__EXEEXT_5) \
	$(am__EXEEXT_6) $(am__EXEEXT_7) $(am__EXEEXT_8) \
	$(am__EXEEXT_9)
DIST_COMMON = $(srcdir)/libhashkit-1.0/include.am \
	$(srcdir)/libhashkit/include.am \
	$(srcdir)/libmemcached/include.am \
	$(srcdir)/libmemcached/csl/include.am \
	$(srcdir)/libmemcached-1.0/include.am \
	$(srcdir)/libmemcached-1.0/struct/include.am \
	$(srcdir)/libmemcached-1.0/types/include.am \
	$(srcdir)/libmemcached-1.0/t/include.am \
	$(srcdir)/libtest/include.am \
	$(srcdir)/libmemcachedprotocol-0.0/include.am \
	$(srcdir)/libmemcachedutil-1.0/include.am \
	$(srcdir)/clients/include.am $(srcdir)/docs/include.am \
	$(srcdir)/man/include.am $(srcdir)/example/include.am \
	$(srcdir)/libmemcachedutil/include.am \
	$(srcdir)/libmemcachedprotocol/include.am \
	$(srcdir)/libmemcachedinternal/include.am \
	$(srcdir)/libmemcachedinternal/util/include.am \
	$(srcdir)/rpm/include.mk $(srcdir)/support/include.am \
	$(srcdir)/tests/include.am \
	$(srcdir)/tests/libmemcached-1.0/include.am \
	$(srcdir)/tests/parser.am $(srcdir)/tests/cli.am \
	$(srcdir)/util/include.am $(srcdir)/win32/include.am \
	$(srcdir)/m4/include.am $(srcdir)/Makefile.in \
	$(srcdir)/Makefile.am $(top_srcdir)/configure \
	$(am__configure_deps) $(srcdir)/mem_config.in \
	$(top_srcdir)/libhashkit/hashkitcon.h.in \
	$(top_srcdir)/libhashkit-1.0/configure.h.in \
	$(top_srcdir)/libtest/version.h.in \
	$(top_srcdir)/libtest/yatlcon.h.in \
	$(top_srcdir)/docs/conf.py.in \
	$(top_srcdir)/libmemcached-1.0/configure.h.in \
	$(top_srcdir)/support/libmemcached.pc.in \
	$(top_srcdir)/support/libmemcached.spec.in \
	$(top_srcdir)/build-aux/depcomp $(dist_man_MANS) \
	$(am__dist_aclocal_DATA_DIST) $(include_HEADERS) \
	$(am__nobase_include_HEADERS_DIST) $(am__noinst_HEADERS_DIST) \
	$(top_srcdir)/build-aux/test-driver AUTHORS COPYING ChangeLog \
	NEWS README THANKS TODO build-aux/config.guess \
	build-aux/config.sub build-aux/depcomp build-aux/install-sh \
	build-aux/missing build-aux/ltmain.sh \
	$(top_srcdir)/build-aux/config.guess \
	$(top_srcdir)/build-aux/config.sub \
	$(top_srcdir)/build-aux/install-sh \
	$(top_srcdir)/build-aux/ltmain.sh \
	$(top_srcdir)/build-aux/missing

am__append_25 = libtest/run.gdb libtest/version.h \
	libhashkit-1.0/configure.h.in \
	libmemcached-1.0/configure.h.in \
	libmemcached/csl/parser.yy \
	libmemcached/csl/scanner.l \
	libmemcached/libmemcached_probes.d \
	libmemcached/memcached/README.txt \
	support/libmemcached.spec \
	support/set_benchmark.sh \
	tests/cpp_example.cc
am__append_26 = libtest/version.h \
	libhashkit-1.0/configure.h \
	libmemcached-1.0/configure.h \
	libmemcached/csl/parser.cc \
	libmemcached/csl/parser.h \
	libmemcached/csl/scanner.cc \
	libmemcached/csl/scanner.h
am__append_27 = libtest/client.hpp \
	libtest/formatter.hpp libtest/timer.hpp \
	libtest/alarm.h libtest/binaries.h \
	libtest/cpu.hpp libtest/blobslap_worker.h \
	libtest/callbacks.h libtest/dns.hpp \
	libtest/cmdline.h libtest/collection.h \
	libtest/common.h libtest/comparison.hpp \
	libtest/core.h libtest/dream.h \
	libtest/error.h libtest/exception.hpp \
	libtest/exception/disconnected.hpp \
	libtest/exception/fatal.hpp \
	libtest/framework.h libtest/gearmand.h \
	libtest/drizzled.h libtest/get.h \
	libtest/has.hpp libtest/http.hpp \
	libtest/is_pid.hpp libtest/is_local.hpp \
	libtest/killpid.h libtest/libtool.hpp \
	libtest/memcached.h libtest/memcached.hpp \
	libtest/poll_error.hpp libtest/port.h \
	libtest/result.hpp libtest/result/base.hpp \
	libtest/result/fail.hpp \
	libtest/result/skip.hpp \
	libtest/result/success.hpp libtest/runner.h \
	libtest/server.h libtest/server_container.h \
	libtest/signal.h libtest/socket.hpp \
	libtest/stream.h libtest/strerror.h \
	libtest/string.hpp libtest/test.h \
	libtest/test.hpp libtest/thread.hpp \
	libtest/tmpfile.hpp libtest/lite.h \
	libtest/valgrind.h libtest/vchar.hpp \
	libtest/version.h libtest/visibility.h \
	libtest/wait.h libtest/yatl.h \
	clients/client_options.h clients/execute.h \
	clients/generator.h clients/ms_atomic.h \
	clients/ms_conn.h clients/ms_memslap.h \
	clients/ms_setting.h clients/ms_sigsegv.h \
	clients/ms_stats.h clients/ms_task.h \
	clients/ms_thread.h clients/utilities.h
am__append_28 = libtest/libtest.la
#am__append_29 = @LIBDRIZZLE_LDFLAGS@
#am__append_30 = @LIBDRIZZLE_LIB@
#am__append_31 = libtest/blobslap_worker.cc
am__append_32 = libtest/unittest libtest/skiptest
am__append_33 = libtest/unittest libtest/skiptest \
	libtest/wait libtest/core-count \
	libtest/abort libtest/backtrace

# Tests for this version of the interface
am__append_34 = libhashkit-1.0/algorithm.h \
	libhashkit-1.0/behavior.h \
	libhashkit-1.0/configure.h \
	libhashkit-1.0/digest.h \
	libhashkit-1.0/function.h \
	libhashkit-1.0/has.h \
	libhashkit-1.0/hashkit.h \
	libhashkit-1.0/hashkit.hpp \
	libhashkit-1.0/strerror.h \
	libhashkit-1.0/string.h \
	libhashkit-1.0/str_algorithm.h \
	libhashkit-1.0/types.h \
	libhashkit-1.0/visibility.h \
	libmemcached-1.0/struct/allocator.h \
	libmemcached-1.0/struct/analysis.h \
	libmemcached-1.0/struct/callback.h \
	libmemcached-1.0/struct/memcached.h \
	libmemcached-1.0/struct/result.h \
	libmemcached-1.0/struct/sasl.h \
	libmemcached-1.0/struct/server.h \
	libmemcached-1.0/struct/stat.h \
	libmemcached-1.0/struct/string.h \
	libmemcached-1.0/types/behavior.h \
	libmemcached-1.0/types/callback.h \
	libmemcached-1.0/types/connection.h \
	libmemcached-1.0/types/hash.h \
	libmemcached-1.0/types/return.h \
	libmemcached-1.0/types/server_distribution.h \
	libmemcached-1.0/alloc.h \
	libmemcached-1.0/allocators.h \
	libmemcached-1.0/analyze.h \
	libmemcached-1.0/auto.h \
	libmemcached-1.0/basic_string.h \
	libmemcached-1.0/behavior.h \
	libmemcached-1.0/callback.h \
	libmemcached-1.0/callbacks.h \
	libmemcached-1.0/configure.h \
	libmemcached-1.0/defaults.h \
	libmemcached-1.0/delete.h \
	libmemcached-1.0/deprecated_types.h \
	libmemcached-1.0/dump.h \
	libmemcached-1.0/encoding_key.h \
	libmemcached-1.0/error.h \
	libmemcached-1.0/exception.hpp \
	libmemcached-1.0/exist.h \
	libmemcached-1.0/fetch.h \
	libmemcached-1.0/flush.h \
	libmemcached-1.0/flush_buffers.h \
	libmemcached-1.0/get.h \
	libmemcached-1.0/hash.h \
	libmemcached-1.0/limits.h \
	libmemcached-1.0/memcached.h \
	libmemcached-1.0/memcached.hpp \
	libmemcached-1.0/options.h \
	libmemcached-1.0/parse.h \
	libmemcached-1.0/platform.h \
	libmemcached-1.0/quit.h \
	libmemcached-1.0/result.h \
	libmemcached-1.0/return.h \
	libmemcached-1.0/sasl.h \
	libmemcached-1.0/server.h \
	libmemcached-1.0/server_list.h \
	libmemcached-1.0/stats.h \
	libmemcached-1.0/storage.h \
	libmemcached-1.0/strerror.h \
	libmemcached-1.0/touch.h \
	libmemcached-1.0/triggers.h \
	libmemcached-1.0/types.h \
	libmemcached-1.0/verbosity.h \
	libmemcached-1.0/version.h \
	libmemcached-1.0/visibility.h
am__append_35 = libmemcached-1.0/t/c_test \
	libmemcached-1.0/t/c_sasl_test
am__append_36 = libmemcached-1.0/t/c_test \
	libmemcached-1.0/t/c_sasl_test
am__append_37 = libmemcached-1.0/t/cc_test \
	tests/cycle
am__append_38 = libmemcached-1.0/t/cc_test

am__append_40 = libmemcachedutil-1.0/flush.h \
	libmemcachedutil-1.0/ostream.hpp \
	libmemcachedutil-1.0/pid.h \
	libmemcachedutil-1.0/ping.h \
	libmemcachedutil-1.0/pool.h \
	libmemcachedutil-1.0/util.h \
	libmemcachedutil-1.0/version.h \
	libhashkit/hashkit.h \
	libmemcached/memcached.h \
	libmemcached/memcached.hpp \
	libmemcached/util.h
am__append_41 = clients/memcapable clients/memcat \
	clients/memcp clients/memdump \
	clients/memerror clients/memexist \
	clients/memtouch clients/memflush \
	clients/memparse clients/memping \
	clients/memrm clients/memslap \
	clients/memstat
am__append_42 = clients/memaslap

# library used for testing

# This noinst lib contains things we want to be ABI private but still want to
# either use in client programs or be able to test in test cases These symbols
# will not be exposed in the shipped .so

# This noinst lib contains things we want to be ABI private but still want to
# either use in client programs or be able to test in test cases These symbols
# will not be exposed in the shipped .so
am__append_43 = clients/libutilities.la \
	libhashkit/libhashkitinc.la \
	libmemcachedinternal/libmemcachedinternal.la \
	libmemcachedinternal/libmemcachedutilinternal.la
am__append_44 = man/memaslap.1 man/memcapable.1 \
	man/memcat.1 man/memcp.1 man/memdump.1 \
	man/memerror.1 man/memexist.1 \
	man/memflush.1 man/memparse.1 man/memping.1 \
	man/memrm.1 man/memslap.1 man/memstat.1 \
	man/memtouch.1 man/hashkit_clone.3 \
	man/hashkit_crc32.3 man/hashkit_create.3 \
	man/hashkit_fnv1_32.3 man/hashkit_fnv1_64.3 \
	man/hashkit_fnv1a_32.3 \
	man/hashkit_fnv1a_64.3 man/hashkit_free.3 \
	man/hashkit_functions.3 man/hashkit_hsieh.3 \
	man/hashkit_is_allocated.3 \
	man/hashkit_jenkins.3 man/hashkit_md5.3 \
	man/hashkit_murmur.3 man/hashkit_value.3 \
	man/libhashkit.3 man/libmemcached.3 \
	man/libmemcached_check_configuration.3 \
	man/libmemcached_configuration.3 \
	man/libmemcached_examples.3 \
	man/libmemcachedutil.3 man/memcached.3 \
	man/memcached_add.3 \
	man/memcached_add_by_key.3 \
	man/memcached_analyze.3 \
	man/memcached_append.3 \
	man/memcached_append_by_key.3 \
	man/memcached_behavior_get.3 \
	man/memcached_behavior_set.3 \
	man/memcached_callback_get.3 \
	man/memcached_callback_set.3 \
	man/memcached_cas.3 \
	man/memcached_cas_by_key.3 \
	man/memcached_clone.3 \
	man/memcached_create.3 \
	man/memcached_decrement.3 \
	man/memcached_decrement_with_initial.3 \
	man/memcached_delete.3 \
	man/memcached_delete_by_key.3 \
	man/memcached_destroy_sasl_auth_data.3 \
	man/memcached_dump.3 man/memcached_exist.3 \
	man/memcached_exist_by_key.3 \
	man/memcached_fetch.3 \
	man/memcached_fetch_execute.3 \
	man/memcached_fetch_result.3 \
	man/memcached_flush_buffers.3 \
	man/memcached_free.3 \
	man/memcached_generate_hash.3 \
	man/memcached_generate_hash_value.3 \
	man/memcached_get.3 \
	man/memcached_get_by_key.3 \
	man/memcached_get_memory_allocators.3 \
	man/memcached_get_sasl_callbacks.3 \
	man/memcached_get_user_data.3 \
	man/memcached_increment.3 \
	man/memcached_increment_with_initial.3 \
	man/memcached_last_error_message.3 \
	man/memcached_lib_version.3 \
	man/memcached_mget.3 \
	man/memcached_mget_by_key.3 \
	man/memcached_mget_execute.3 \
	man/memcached_mget_execute_by_key.3 \
	man/memcached_pool.3 \
	man/memcached_pool_behavior_get.3 \
	man/memcached_pool_behavior_set.3 \
	man/memcached_pool_create.3 \
	man/memcached_pool_destroy.3 \
	man/memcached_pool_fetch.3 \
	man/memcached_pool_pop.3 \
	man/memcached_pool_push.3 \
	man/memcached_pool_release.3 \
	man/memcached_pool_st.3 \
	man/memcached_prepend.3 \
	man/memcached_prepend_by_key.3 \
	man/memcached_quit.3 \
	man/memcached_replace.3 \
	man/memcached_replace_by_key.3 \
	man/memcached_sasl_set_auth_data.3 \
	man/memcached_server_add.3 \
	man/memcached_server_count.3 \
	man/memcached_server_cursor.3 \
	man/memcached_server_list.3 \
	man/memcached_server_list_append.3 \
	man/memcached_server_list_count.3 \
	man/memcached_server_list_free.3 \
	man/memcached_server_push.3 \
	man/memcached_servers_parse.3 \
	man/memcached_set.3 \
	man/memcached_set_by_key.3 \
	man/memcached_set_memory_allocators.3 \
	man/memcached_set_sasl_callbacks.3 \
	man/memcached_set_user_data.3 \
	man/memcached_stat.3 \
	man/memcached_stat_execute.3 \
	man/memcached_stat_get_keys.3 \
	man/memcached_stat_get_value.3 \
	man/memcached_stat_servername.3 \
	man/memcached_strerror.3 \
	man/memcached_touch.3 \
	man/memcached_touch_by_key.3 \
	man/memcached_verbosity.3 \
	man/memcached_version.3
#am__append_45 = example/memcached_light
#am__append_46 = example/byteorder.h \
#	example/memcached_light.h \
#	example/storage.h
am__append_47 = libhashkit/libhashkit.la \
	libmemcached/libmemcached.la \
	libmemcached/libmemcachedutil.la
am__append_48 = libhashkit/aes.h \
	libhashkit/algorithm.h libhashkit/murmur3.h \
	libhashkit/common.h libhashkit/is.h \
	libhashkit/rijndael.hpp libhashkit/string.h \
	libmemcached/csl/common.h \
	libmemcached/csl/context.h \
	libmemcached/csl/parser.h \
	libmemcached/csl/scanner.h \
	libmemcached/csl/server.h \
	libmemcached/csl/symbol.h \
	libmemcached/array.h \
	libmemcached/assert.hpp \
	libmemcached/backtrace.hpp \
	libmemcached/behavior.hpp \
	libmemcached/byteorder.h \
	libmemcached/common.h \
	libmemcached/connect.hpp \
	libmemcached/continuum.hpp \
	libmemcached/do.hpp \
	libmemcached/encoding_key.h \
	libmemcached/error.hpp \
	libmemcached/flag.hpp \
	libmemcached/initialize_query.h \
	libmemcached/instance.hpp \
	libmemcached/internal.h libmemcached/io.h \
	libmemcached/io.hpp libmemcached/is.h \
	libmemcached/key.hpp \
	libmemcached/libmemcached_probes.h \
	libmemcached/memcached/protocol_binary.h \
	libmemcached/memcached/vbucket.h \
	libmemcached/memory.h \
	libmemcached/namespace.h \
	libmemcached/options.hpp \
	libmemcached/poll.h libmemcached/response.h \
	libmemcached/result.h libmemcached/sasl.hpp \
	libmemcached/server.hpp \
	libmemcached/server_instance.h \
	libmemcached/socket.hpp \
	libmemcached/string.hpp \
	libmemcached/udp.hpp \
	libmemcached/version.hpp \
	libmemcached/virtual_bucket.h \
	libmemcached/watchpoint.h \
	libmemcached/windows.hpp \
	libmemcachedutil/common.h
#am__append_49 = libhashkit/hsieh.cc
am__append_50 = libhashkit/nohsieh.cc
am__append_51 = libmemcached/csl/parser.output
am__append_52 = libmemcached/csl/parser.h \
	libmemcached/csl/parser.cc \
	libmemcached/csl/scanner.h \
	libmemcached/csl/scanner.cc
#am__append_53 = -pthread
#am__append_54 = -pthread
#am__append_55 =  \
#	 $(am__empty)
#am__append_56 = libmemcached/dtrace_probes.h
#am__append_57 = libmemcached/dtrace_probes.h \
#	libmemcached/libmemcached_probes.o
#am__append_58 = libmemcached/libmemcached_probes.o
#am__append_59 = libmemcached/libmemcached_probes.o
#am__append_60 = libmemcached/libmemcached_probes.d
am__append_61 = .d
#am__append_62 = libmemcached/libmemcachedprotocol.la
#am__append_63 = libmemcachedprotocol/ascii_handler.h \
#	libmemcachedprotocol/binary_handler.h \
#	libmemcachedprotocol/cache.h \
#	libmemcachedprotocol/common.h

# vim:ft=automake
# included from Top Level Makefile.am
# All paths should be given relative to the root
am__append_64 = tests/exist.h tests/hash_results.h \
	tests/keys.hpp \
	tests/libmemcached_test_container.h \
	tests/libmemcached_world.h \
	tests/libmemcached_world_socket.h \
	tests/memc.hpp tests/runner.h tests/basic.h \
	tests/callbacks.h tests/debug.h \
	tests/deprecated.h tests/error_conditions.h \
	tests/exist.h tests/ketama.h \
	tests/ketama_test_cases.h \
	tests/ketama_test_cases_spy.h \
	tests/libmemcached-1.0/all_tests.h \
	tests/libmemcached-1.0/callback_counter.h \
	tests/libmemcached-1.0/dump.h \
	tests/libmemcached-1.0/encoding_key.h \
	tests/libmemcached-1.0/fetch_all_results.h \
	tests/libmemcached-1.0/generate.h \
	tests/libmemcached-1.0/haldenbrand.h \
	tests/libmemcached-1.0/mem_functions.h \
	tests/libmemcached-1.0/memcached_get.h \
	tests/libmemcached-1.0/parser.h \
	tests/libmemcached-1.0/setup_and_teardowns.h \
	tests/libmemcached-1.0/stat.h \
	tests/namespace.h tests/pool.h \
	tests/print.h tests/replication.h \
	tests/server_add.h tests/string.h \
	tests/touch.h tests/virtual_buckets.h \
	tests/libmemcached-1.0/parser.h \
	util/daemon.hpp util/instance.hpp \
	util/logfile.hpp util/log.hpp \
	util/operation.hpp util/signal.hpp \
	util/string.hpp util/pidfile.hpp \
	win32/wrappers.h
am__append_65 = tests/cycle
am__append_66 = tests/libmemcached-1.0/internals
am__append_67 = tests/libmemcached-1.0/internals
am__append_68 = tests/libmemcached-1.0/testapp \
	tests/libmemcached-1.0/testsocket \
	tests/libmemcached-1.0/sasl tests/testudp \
	tests/testplus tests/parser tests/failure \
	tests/testhashkit tests/hash_plus \
	tests/memcapable tests/memstat tests/memcp \
	tests/memflush tests/memrm tests/memexist \
	tests/memtouch tests/memcat tests/memping \
	tests/memerror tests/memslap tests/memdump
am__append_69 = tests/libmemcached-1.0/testapp \
	tests/libmemcached-1.0/testsocket \
	tests/libmemcached-1.0/sasl \
	tests/atomsmasher tests/testudp \
	tests/testplus tests/parser tests/failure \
	tests/testhashkit tests/hash_plus \
	tests/memcapable tests/memstat tests/memcp \
	tests/memflush tests/memrm tests/memexist \
	tests/memtouch tests/memcat tests/memping \
	tests/memerror tests/memslap tests/memdump
#am__append_70 = -no-undefined
#am__append_71 = -no-undefined
##am__append_72 = -no-undefined
#am__append_73 = -no-undefined
am__append_74 = m4/ax_libmemcached.m4
subdir = .
ACLOCAL_M4 = $(top_srcdir)/aclocal.m4
am__aclocal_m4_deps = $(top_srcdir)/m4/ax_add_am_macro.m4 \
	$(top_srcdir)/m4/ax_am_jobserver.m4 \
	$(top_srcdir)/m4/ax_am_macros.m4 \
	$(top_srcdir)/m4/ax_append_compile_flags.m4 \
	$(top_srcdir)/m4/ax_append_flag.m4 \
	$(top_srcdir)/m4/ax_append_link_flags.m4 \
	$(top_srcdir)/m4/ax_append_to_file.m4 \
	$(top_srcdir)/m4/ax_assert.m4 \
	$(top_srcdir)/m4/ax_check_compile_flag.m4 \
	$(top_srcdir)/m4/ax_check_library.m4 \
	$(top_srcdir)/m4/ax_check_link_flag.m4 \
	$(top_srcdir)/m4/ax_compiler_vendor.m4 \
	$(top_srcdir)/m4/ax_compiler_version.m4 \
	$(top_srcdir)/m4/ax_count_cpus.m4 \
	$(top_srcdir)/m4/ax_cxx_gcc_abi_demangle.m4 \
	$(top_srcdir)/m4/ax_debug.m4 $(top_srcdir)/m4/ax_endian.m4 \
	$(top_srcdir)/m4/ax_file_escapes.m4 \
	$(top_srcdir)/m4/ax_gcc_atomic_builtins.m4 \
	$(top_srcdir)/m4/ax_harden_compiler_flags.m4 \
	$(top_srcdir)/m4/ax_hex_version.m4 \
	$(top_srcdir)/m4/ax_libevent.m4 \
	$(top_srcdir)/m4/ax_memcached.m4 \
	$(top_srcdir)/m4/ax_platform.m4 \
	$(top_srcdir)/m4/ax_print_to_file.m4 \
	$(top_srcdir)/m4/ax_prog_sphinx_build.m4 \
	$(top_srcdir)/m4/ax_pthread.m4 \
	$(top_srcdir)/m4/ax_pthread_timedjoin_np.m4 \
	$(top_srcdir)/m4/ax_restore_flags.m4 \
	$(top_srcdir)/m4/ax_sasl.m4 $(top_srcdir)/m4/ax_save_flags.m4 \
	$(top_srcdir)/m4/ax_uuid.m4 \
	$(top_srcdir)/m4/ax_vcs_checkout.m4 \
	$(top_srcdir)/m4/ax_with_prog.m4 $(top_srcdir)/m4/bottom.m4 \
	$(top_srcdir)/m4/byteorder.m4 $(top_srcdir)/m4/deprecated.m4 \
	$(top_srcdir)/m4/fnv.m4 $(top_srcdir)/m4/gearmand.m4 \
	$(top_srcdir)/m4/have_cinttypes.m4 \
	$(top_srcdir)/m4/have_cstdint.m4 $(top_srcdir)/m4/hsieh.m4 \
	$(top_srcdir)/m4/libgearman.m4 $(top_srcdir)/m4/libtool.m4 \
	$(top_srcdir)/m4/ltoptions.m4 $(top_srcdir)/m4/ltsugar.m4 \
	$(top_srcdir)/m4/ltversion.m4 $(top_srcdir)/m4/lt~obsolete.m4 \
	$(top_srcdir)/m4/memaslap.m4 $(top_srcdir)/m4/murmur.m4 \
	$(top_srcdir)/m4/pandora_enable_dtrace.m4 \
	$(top_srcdir)/m4/protocol_binary.m4 \
	$(top_srcdir)/m4/setsockopt.m4 \
	$(top_srcdir)/m4/socket_send_flags.m4 \
	$(top_srcdir)/m4/visibility.m4 $(top_srcdir)/version.m4 \
	$(top_srcdir)/libhashkit/include.m4 \
	$(top_srcdir)/libtest/yatl.m4 \
	$(top_srcdir)/libtest/m4/mysql.m4 \
	$(top_srcdir)/libtest/m4/ax_lib_mysql.m4 \
	$(top_srcdir)/libtest/m4/ax_prog_mysqld.m4 \
	$(top_srcdir)/configure.ac
am__configure_deps = $(am__aclocal_m4_deps) $(CONFIGURE_DEPENDENCIES) \
	$(ACLOCAL_M4)
am__CONFIG_DISTCLEAN_FILES = config.status config.cache config.log \
 configure.lineno config.status.lineno
mkinstalldirs = $(install_sh) -d
CONFIG_HEADER = mem_config.h
CONFIG_CLEAN_FILES = libhashkit/hashkitcon.h \
	libhashkit-1.0/configure.h libtest/version.h libtest/yatlcon.h \
	docs/conf.py libmemcached-1.0/configure.h \
	support/libmemcached.pc support/libmemcached.spec
CONFIG_CLEAN_VPATH_FILES =
am__vpath_adj_setup = srcdirstrip=`echo "$(srcdir)" | sed 's|.|.|g'`;
am__vpath_adj = case $$p in \
    $(srcdir)/*) f=`echo "$$p" | sed "s|^$$srcdirstrip/||"`;; \
    *) f=$$p;; \
  esac;
am__strip_dir = f=`echo $$p | sed -e 's|^.*/||'`;
am__install_max = 40
am__nobase_strip_setup = \
  srcdirstrip=`echo "$(srcdir)" | sed 's/[].[^$$\\*|]/\\\\&/g'`
am__nobase_strip = \
  for p in $$list; do echo "$$p"; done | sed -e "s|$$srcdirstrip/||"
am__nobase_list = $(am__nobase_strip_setup); \
  for p in $$list; do echo "$$p $$p"; done | \
  sed "s| $$srcdirstrip/| |;"' / .*\//!s/ .*/ ./; s,\( .*\)/[^/]*$$,\1,' | \
  $(AWK) 'BEGIN { files["."] = "" } { files[$$2] = files[$$2] " " $$1; \
    if (++n[$$2] == $(am__install_max)) \
      { print $$2, files[$$2]; n[$$2] = 0; files[$$2] = "" } } \
    END { for (dir in files) print dir, files[dir] }'
am__base_list = \
  sed '$$!N;$$!N;$$!N;$$!N;$$!N;$$!N;$$!N;s/\n/ /g' | \
  sed '$$!N;$$!N;$$!N;$$!N;s/\n/ /g'
am__uninstall_files_from_dir = { \
  test -z "$$files" \
    || { test ! -d "$$dir" && test ! -f "$$dir" && test ! -r "$$dir"; } \
    || { echo " ( cd '$$dir' && rm -f" $$files ")"; \
         $(am__cd) "$$dir" && rm -f $$files; }; \
  }
am__installdirs = "$(DESTDIR)$(libdir)" "$(DESTDIR)$(bindir)" \
	"$(DESTDIR)$(man1dir)" "$(DESTDIR)$(man3dir)" \
	"$(DESTDIR)$(aclocaldir)" "$(DESTDIR)$(pkgconfigdir)" \
	"$(DESTDIR)$(includedir)" "$(DESTDIR)$(includedir)"
LTLIBRARIES = $(lib_LTLIBRARIES) $(noinst_LTLIBRARIES)
clients_libutilities_la_LIBADD =
am__clients_libutilities_la_SOURCES_DIST = clients/utilities.cc
am__dirstamp = $(am__leading_dot)dirstamp
am_clients_libutilities_la_OBJECTS =  \
	clients/utilities.lo
clients_libutilities_la_OBJECTS =  \
	$(am_clients_libutilities_la_OBJECTS)
AM_V_lt = $(am__v_lt_$(V))
am__v_lt_ = $(am__v_lt_$(AM_DEFAULT_VERBOSITY))
am__v_lt_0 = --silent
am__v_lt_1 =
am_clients_libutilities_la_rpath =
libhashkit_libhashkit_la_DEPENDENCIES =
am__libhashkit_libhashkit_la_SOURCES_DIST = libhashkit/aes.cc \
	libhashkit/algorithm.cc libhashkit/behavior.cc \
	libhashkit/crc32.cc libhashkit/digest.cc libhashkit/encrypt.cc \
	libhashkit/fnv_32.cc libhashkit/fnv_64.cc \
	libhashkit/function.cc libhashkit/has.cc libhashkit/hashkit.cc \
	libhashkit/jenkins.cc libhashkit/ketama.cc libhashkit/md5.cc \
	libhashkit/murmur.cc libhashkit/murmur3.cc \
	libhashkit/murmur3_api.cc libhashkit/one_at_a_time.cc \
	libhashkit/rijndael.cc libhashkit/str_algorithm.cc \
	libhashkit/strerror.cc libhashkit/string.cc \
	libhashkit/hsieh.cc libhashkit/nohsieh.cc
#am__objects_1 = libhashkit/libhashkit_libhashkit_la-hsieh.lo
am__objects_2 = libhashkit/libhashkit_libhashkit_la-nohsieh.lo
##am__objects_3 = libhashkit/libhashkit_libhashkit_la-hsieh.lo
#am__objects_4 = libhashkit/libhashkit_libhashkit_la-nohsieh.lo
am_libhashkit_libhashkit_la_OBJECTS =  \
	libhashkit/libhashkit_libhashkit_la-aes.lo \
	libhashkit/libhashkit_libhashkit_la-algorithm.lo \
	libhashkit/libhashkit_libhashkit_la-behavior.lo \
	libhashkit/libhashkit_libhashkit_la-crc32.lo \
	libhashkit/libhashkit_libhashkit_la-digest.lo \
	libhashkit/libhashkit_libhashkit_la-encrypt.lo \
	libhashkit/libhashkit_libhashkit_la-fnv_32.lo \
	libhashkit/libhashkit_libhashkit_la-fnv_64.lo \
	libhashkit/libhashkit_libhashkit_la-function.lo \
	libhashkit/libhashkit_libhashkit_la-has.lo \
	libhashkit/libhashkit_libhashkit_la-hashkit.lo \
	libhashkit/libhashkit_libhashkit_la-jenkins.lo \
	libhashkit/libhashkit_libhashkit_la-ketama.lo \
	libhashkit/libhashkit_libhashkit_la-md5.lo \
	libhashkit/libhashkit_libhashkit_la-murmur.lo \
	libhashkit/libhashkit_libhashkit_la-murmur3.lo \
	libhashkit/libhashkit_libhashkit_la-murmur3_api.lo \
	libhashkit/libhashkit_libhashkit_la-one_at_a_time.lo \
	libhashkit/libhashkit_libhashkit_la-rijndael.lo \
	libhashkit/libhashkit_libhashkit_la-str_algorithm.lo \
	libhashkit/libhashkit_libhashkit_la-strerror.lo \
	libhashkit/libhashkit_libhashkit_la-string.lo \
	$(am__objects_1) $(am__objects_2)
#am_libhashkit_libhashkit_la_OBJECTS =  \
#	libhashkit/libhashkit_libhashkit_la-aes.lo \
#	libhashkit/libhashkit_libhashkit_la-algorithm.lo \
#	libhashkit/libhashkit_libhashkit_la-behavior.lo \
#	libhashkit/libhashkit_libhashkit_la-crc32.lo \
#	libhashkit/libhashkit_libhashkit_la-digest.lo \
#	libhashkit/libhashkit_libhashkit_la-encrypt.lo \
#	libhashkit/libhashkit_libhashkit_la-fnv_32.lo \
#	libhashkit/libhashkit_libhashkit_la-fnv_64.lo \
#	libhashkit/libhashkit_libhashkit_la-function.lo \
#	libhashkit/libhashkit_libhashkit_la-has.lo \
#	libhashkit/libhashkit_libhashkit_la-hashkit.lo \
#	libhashkit/libhashkit_libhashkit_la-jenkins.lo \
#	libhashkit/libhashkit_libhashkit_la-ketama.lo \
#	libhashkit/libhashkit_libhashkit_la-md5.lo \
#	libhashkit/libhashkit_libhashkit_la-murmur.lo \
#	libhashkit/libhashkit_libhashkit_la-murmur3.lo \
#	libhashkit/libhashkit_libhashkit_la-murmur3_api.lo \
#	libhashkit/libhashkit_libhashkit_la-one_at_a_time.lo \
#	libhashkit/libhashkit_libhashkit_la-rijndael.lo \
#	libhashkit/libhashkit_libhashkit_la-str_algorithm.lo \
#	libhashkit/libhashkit_libhashkit_la-strerror.lo \
#	libhashkit/libhashkit_libhashkit_la-string.lo \
#	$(am__objects_3) $(am__objects_4) \
#	$(am__objects_1) $(am__objects_2)
libhashkit_libhashkit_la_OBJECTS =  \
	$(am_libhashkit_libhashkit_la_OBJECTS)
libhashkit_libhashkit_la_LINK = $(LIBTOOL) $(AM_V_lt) --tag=CXX \
	$(AM_LIBTOOLFLAGS) $(LIBTOOLFLAGS) --mode=link $(CXXLD) \
	$(libhashkit_libhashkit_la_CXXFLAGS) $(CXXFLAGS) \
	$(libhashkit_libhashkit_la_LDFLAGS) $(LDFLAGS) -o $@
am_libhashkit_libhashkit_la_rpath = -rpath \
	$(libdir)
#am_libhashkit_libhashkit_la_rpath = -rpath $(libdir)
libhashkit_libhashkitinc_la_LIBADD =
am__libhashkit_libhashkitinc_la_SOURCES_DIST = libhashkit/aes.cc \
	libhashkit/algorithm.cc libhashkit/behavior.cc \
	libhashkit/crc32.cc libhashkit/digest.cc libhashkit/encrypt.cc \
	libhashkit/fnv_32.cc libhashkit/fnv_64.cc \
	libhashkit/function.cc libhashkit/has.cc libhashkit/hashkit.cc \
	libhashkit/jenkins.cc libhashkit/ketama.cc libhashkit/md5.cc \
	libhashkit/murmur.cc libhashkit/murmur3.cc \
	libhashkit/murmur3_api.cc libhashkit/one_at_a_time.cc \
	libhashkit/rijndael.cc libhashkit/str_algorithm.cc \
	libhashkit/strerror.cc libhashkit/string.cc \
	libhashkit/hsieh.cc libhashkit/nohsieh.cc
#am__objects_5 = libhashkit/libhashkit_libhashkitinc_la-hsieh.lo
am__objects_6 = libhashkit/libhashkit_libhashkitinc_la-nohsieh.lo
##am__objects_7 = libhashkit/libhashkit_libhashkitinc_la-hsieh.lo
#am__objects_8 = libhashkit/libhashkit_libhashkitinc_la-nohsieh.lo
am__objects_9 = libhashkit/libhashkit_libhashkitinc_la-aes.lo \
	libhashkit/libhashkit_libhashkitinc_la-algorithm.lo \
	libhashkit/libhashkit_libhashkitinc_la-behavior.lo \
	libhashkit/libhashkit_libhashkitinc_la-crc32.lo \
	libhashkit/libhashkit_libhashkitinc_la-digest.lo \
	libhashkit/libhashkit_libhashkitinc_la-encrypt.lo \
	libhashkit/libhashkit_libhashkitinc_la-fnv_32.lo \
	libhashkit/libhashkit_libhashkitinc_la-fnv_64.lo \
	libhashkit/libhashkit_libhashkitinc_la-function.lo \
	libhashkit/libhashkit_libhashkitinc_la-has.lo \
	libhashkit/libhashkit_libhashkitinc_la-hashkit.lo \
	libhashkit/libhashkit_libhashkitinc_la-jenkins.lo \
	libhashkit/libhashkit_libhashkitinc_la-ketama.lo \
	libhashkit/libhashkit_libhashkitinc_la-md5.lo \
	libhashkit/libhashkit_libhashkitinc_la-murmur.lo \
	libhashkit/libhashkit_libhashkitinc_la-murmur3.lo \
	libhashkit/libhashkit_libhashkitinc_la-murmur3_api.lo \
	libhashkit/libhashkit_libhashkitinc_la-one_at_a_time.lo \
	libhashkit/libhashkit_libhashkitinc_la-rijndael.lo \
	libhashkit/libhashkit_libhashkitinc_la-str_algorithm.lo \
	libhashkit/libhashkit_libhashkitinc_la-strerror.lo \
	libhashkit/libhashkit_libhashkitinc_la-string.lo \
	$(am__objects_5) $(am__objects_6)
#am__objects_9 = libhashkit/libhashkit_libhashkitinc_la-aes.lo \
#	libhashkit/libhashkit_libhashkitinc_la-algorithm.lo \
#	libhashkit/libhashkit_libhashkitinc_la-behavior.lo \
#	libhashkit/libhashkit_libhashkitinc_la-crc32.lo \
#	libhashkit/libhashkit_libhashkitinc_la-digest.lo \
#	libhashkit/libhashkit_libhashkitinc_la-encrypt.lo \
#	libhashkit/libhashkit_libhashkitinc_la-fnv_32.lo \
#	libhashkit/libhashkit_libhashkitinc_la-fnv_64.lo \
#	libhashkit/libhashkit_libhashkitinc_la-function.lo \
#	libhashkit/libhashkit_libhashkitinc_la-has.lo \
#	libhashkit/libhashkit_libhashkitinc_la-hashkit.lo \
#	libhashkit/libhashkit_libhashkitinc_la-jenkins.lo \
#	libhashkit/libhashkit_libhashkitinc_la-ketama.lo \
#	libhashkit/libhashkit_libhashkitinc_la-md5.lo \
#	libhashkit/libhashkit_libhashkitinc_la-murmur.lo \
#	libhashkit/libhashkit_libhashkitinc_la-murmur3.lo \
#	libhashkit/libhashkit_libhashkitinc_la-murmur3_api.lo \
#	libhashkit/libhashkit_libhashkitinc_la-one_at_a_time.lo \
#	libhashkit/libhashkit_libhashkitinc_la-rijndael.lo \
#	libhashkit/libhashkit_libhashkitinc_la-str_algorithm.lo \
#	libhashkit/libhashkit_libhashkitinc_la-strerror.lo \
#	libhashkit/libhashkit_libhashkitinc_la-string.lo \
#	$(am__objects_7) $(am__objects_8) \
#	$(am__objects_5) $(am__objects_6)
am_libhashkit_libhashkitinc_la_OBJECTS =  \
	$(am__objects_9)
#am_libhashkit_libhashkitinc_la_OBJECTS =  \
#	$(am__objects_9)
libhashkit_libhashkitinc_la_OBJECTS =  \
	$(am_libhashkit_libhashkitinc_la_OBJECTS)
libhashkit_libhashkitinc_la_LINK = $(LIBTOOL) $(AM_V_lt) --tag=CXX \
	$(AM_LIBTOOLFLAGS) $(LIBTOOLFLAGS) --mode=link $(CXXLD) \
	$(libhashkit_libhashkitinc_la_CXXFLAGS) $(CXXFLAGS) \
	$(AM_LDFLAGS) $(LDFLAGS) -o $@
am_libhashkit_libhashkitinc_la_rpath =
#am_libhashkit_libhashkitinc_la_rpath =
am__DEPENDENCIES_1 =
libmemcached_libmemcached_la_DEPENDENCIES =  \
	$(am__DEPENDENCIES_1) $(am__append_59)
#libmemcached_libmemcached_la_DEPENDENCIES =  \
#	$(am__DEPENDENCIES_1) $(am__append_17) \
#	$(am__DEPENDENCIES_1) $(am__append_59)
am__libmemcached_libmemcached_la_SOURCES_DIST =  \
	libmemcached/csl/context.cc libmemcached/csl/parser.cc \
	libmemcached/csl/scanner.cc libmemcached/instance.cc \
	libhashkit/aes.cc libhashkit/algorithm.cc \
	libhashkit/behavior.cc libhashkit/crc32.cc \
	libhashkit/digest.cc libhashkit/encrypt.cc \
	libhashkit/fnv_32.cc libhashkit/fnv_64.cc \
	libhashkit/function.cc libhashkit/has.cc libhashkit/hashkit.cc \
	libhashkit/jenkins.cc libhashkit/ketama.cc libhashkit/md5.cc \
	libhashkit/murmur.cc libhashkit/murmur3.cc \
	libhashkit/murmur3_api.cc libhashkit/one_at_a_time.cc \
	libhashkit/rijndael.cc libhashkit/str_algorithm.cc \
	libhashkit/strerror.cc libhashkit/string.cc \
	libhashkit/hsieh.cc libhashkit/nohsieh.cc \
	libmemcached/allocators.cc libmemcached/allocators.hpp \
	libmemcached/analyze.cc libmemcached/array.c \
	libmemcached/auto.cc libmemcached/backtrace.cc \
	libmemcached/behavior.cc libmemcached/byteorder.cc \
	libmemcached/callback.cc libmemcached/connect.cc \
	libmemcached/delete.cc libmemcached/do.cc libmemcached/dump.cc \
	libmemcached/error.cc libmemcached/exist.cc \
	libmemcached/fetch.cc libmemcached/flag.cc \
	libmemcached/flush.cc libmemcached/flush_buffers.cc \
	libmemcached/get.cc libmemcached/hash.cc libmemcached/hash.hpp \
	libmemcached/hosts.cc libmemcached/initialize_query.cc \
	libmemcached/io.cc libmemcached/key.cc \
	libmemcached/memcached.cc libmemcached/encoding_key.cc \
	libmemcached/namespace.cc libmemcached/options.cc \
	libmemcached/parse.cc libmemcached/poll.cc \
	libmemcached/purge.cc libmemcached/quit.cc \
	libmemcached/quit.hpp libmemcached/response.cc \
	libmemcached/result.cc libmemcached/sasl.cc \
	libmemcached/server.cc libmemcached/server_list.cc \
	libmemcached/server_list.hpp libmemcached/stats.cc \
	libmemcached/storage.cc libmemcached/strerror.cc \
	libmemcached/string.cc libmemcached/touch.cc \
	libmemcached/udp.cc libmemcached/verbosity.cc \
	libmemcached/version.cc libmemcached/virtual_bucket.c \
	libmemcached/libmemcached_probes.d
#am__objects_10 = libhashkit/libmemcached_libmemcached_la-hsieh.lo
am__objects_11 = libhashkit/libmemcached_libmemcached_la-nohsieh.lo
##am__objects_12 = libhashkit/libmemcached_libmemcached_la-hsieh.lo
#am__objects_13 = libhashkit/libmemcached_libmemcached_la-nohsieh.lo
am__objects_14 = libhashkit/libmemcached_libmemcached_la-aes.lo \
	libhashkit/libmemcached_libmemcached_la-algorithm.lo \
	libhashkit/libmemcached_libmemcached_la-behavior.lo \
	libhashkit/libmemcached_libmemcached_la-crc32.lo \
	libhashkit/libmemcached_libmemcached_la-digest.lo \
	libhashkit/libmemcached_libmemcached_la-encrypt.lo \
	libhashkit/libmemcached_libmemcached_la-fnv_32.lo \
	libhashkit/libmemcached_libmemcached_la-fnv_64.lo \
	libhashkit/libmemcached_libmemcached_la-function.lo \
	libhashkit/libmemcached_libmemcached_la-has.lo \
	libhashkit/libmemcached_libmemcached_la-hashkit.lo \
	libhashkit/libmemcached_libmemcached_la-jenkins.lo \
	libhashkit/libmemcached_libmemcached_la-ketama.lo \
	libhashkit/libmemcached_libmemcached_la-md5.lo \
	libhashkit/libmemcached_libmemcached_la-murmur.lo \
	libhashkit/libmemcached_libmemcached_la-murmur3.lo \
	libhashkit/libmemcached_libmemcached_la-murmur3_api.lo \
	libhashkit/libmemcached_libmemcached_la-one_at_a_time.lo \
	libhashkit/libmemcached_libmemcached_la-rijndael.lo \
	libhashkit/libmemcached_libmemcached_la-str_algorithm.lo \
	libhashkit/libmemcached_libmemcached_la-strerror.lo \
	libhashkit/libmemcached_libmemcached_la-string.lo \
	$(am__objects_10) $(am__objects_11)
#am__objects_14 = libhashkit/libmemcached_libmemcached_la-aes.lo \
#	libhashkit/libmemcached_libmemcached_la-algorithm.lo \
#	libhashkit/libmemcached_libmemcached_la-behavior.lo \
#	libhashkit/libmemcached_libmemcached_la-crc32.lo \
#	libhashkit/libmemcached_libmemcached_la-digest.lo \
#	libhashkit/libmemcached_libmemcached_la-encrypt.lo \
#	libhashkit/libmemcached_libmemcached_la-fnv_32.lo \
#	libhashkit/libmemcached_libmemcached_la-fnv_64.lo \
#	libhashkit/libmemcached_libmemcached_la-function.lo \
#	libhashkit/libmemcached_libmemcached_la-has.lo \
#	libhashkit/libmemcached_libmemcached_la-hashkit.lo \
#	libhashkit/libmemcached_libmemcached_la-jenkins.lo \
#	libhashkit/libmemcached_libmemcached_la-ketama.lo \
#	libhashkit/libmemcached_libmemcached_la-md5.lo \
#	libhashkit/libmemcached_libmemcached_la-murmur.lo \
#	libhashkit/libmemcached_libmemcached_la-murmur3.lo \
#	libhashkit/libmemcached_libmemcached_la-murmur3_api.lo \
#	libhashkit/libmemcached_libmemcached_la-one_at_a_time.lo \
#	libhashkit/libmemcached_libmemcached_la-rijndael.lo \
#	libhashkit/libmemcached_libmemcached_la-str_algorithm.lo \
#	libhashkit/libmemcached_libmemcached_la-strerror.lo \
#	libhashkit/libmemcached_libmemcached_la-string.lo \
#	$(am__objects_12) $(am__objects_13) \
#	$(am__objects_10) $(am__objects_11)
am__objects_15 =
am_libmemcached_libmemcached_la_OBJECTS = libmemcached/csl/libmemcached_libmemcached_la-context.lo \
	libmemcached/csl/libmemcached_libmemcached_la-parser.lo \
	libmemcached/csl/libmemcached_libmemcached_la-scanner.lo \
	libmemcached/libmemcached_libmemcached_la-instance.lo \
	$(am__objects_14) \
	libmemcached/libmemcached_libmemcached_la-allocators.lo \
	libmemcached/libmemcached_libmemcached_la-analyze.lo \
	libmemcached/libmemcached_libmemcached_la-array.lo \
	libmemcached/libmemcached_libmemcached_la-auto.lo \
	libmemcached/libmemcached_libmemcached_la-backtrace.lo \
	libmemcached/libmemcached_libmemcached_la-behavior.lo \
	libmemcached/libmemcached_libmemcached_la-byteorder.lo \
	libmemcached/libmemcached_libmemcached_la-callback.lo \
	libmemcached/libmemcached_libmemcached_la-connect.lo \
	libmemcached/libmemcached_libmemcached_la-delete.lo \
	libmemcached/libmemcached_libmemcached_la-do.lo \
	libmemcached/libmemcached_libmemcached_la-dump.lo \
	libmemcached/libmemcached_libmemcached_la-error.lo \
	libmemcached/libmemcached_libmemcached_la-exist.lo \
	libmemcached/libmemcached_libmemcached_la-fetch.lo \
	libmemcached/libmemcached_libmemcached_la-flag.lo \
	libmemcached/libmemcached_libmemcached_la-flush.lo \
	libmemcached/libmemcached_libmemcached_la-flush_buffers.lo \
	libmemcached/libmemcached_libmemcached_la-get.lo \
	libmemcached/libmemcached_libmemcached_la-hash.lo \
	libmemcached/libmemcached_libmemcached_la-hosts.lo \
	libmemcached/libmemcached_libmemcached_la-initialize_query.lo \
	libmemcached/libmemcached_libmemcached_la-io.lo \
	libmemcached/libmemcached_libmemcached_la-key.lo \
	libmemcached/libmemcached_libmemcached_la-memcached.lo \
	libmemcached/libmemcached_libmemcached_la-encoding_key.lo \
	libmemcached/libmemcached_libmemcached_la-namespace.lo \
	libmemcached/libmemcached_libmemcached_la-options.lo \
	libmemcached/libmemcached_libmemcached_la-parse.lo \
	libmemcached/libmemcached_libmemcached_la-poll.lo \
	libmemcached/libmemcached_libmemcached_la-purge.lo \
	libmemcached/libmemcached_libmemcached_la-quit.lo \
	libmemcached/libmemcached_libmemcached_la-response.lo \
	libmemcached/libmemcached_libmemcached_la-result.lo \
	libmemcached/libmemcached_libmemcached_la-sasl.lo \
	libmemcached/libmemcached_libmemcached_la-server.lo \
	libmemcached/libmemcached_libmemcached_la-server_list.lo \
	libmemcached/libmemcached_libmemcached_la-stats.lo \
	libmemcached/libmemcached_libmemcached_la-storage.lo \
	libmemcached/libmemcached_libmemcached_la-strerror.lo \
	libmemcached/libmemcached_libmemcached_la-string.lo \
	libmemcached/libmemcached_libmemcached_la-touch.lo \
	libmemcached/libmemcached_libmemcached_la-udp.lo \
	libmemcached/libmemcached_libmemcached_la-verbosity.lo \
	libmemcached/libmemcached_libmemcached_la-version.lo \
	libmemcached/libmemcached_libmemcached_la-virtual_bucket.lo \
	$(am__objects_15)
#am_libmemcached_libmemcached_la_OBJECTS = libmemcached/csl/libmemcached_libmemcached_la-context.lo \
#	libmemcached/csl/libmemcached_libmemcached_la-parser.lo \
#	libmemcached/csl/libmemcached_libmemcached_la-scanner.lo \
#	libmemcached/libmemcached_libmemcached_la-instance.lo \
#	$(am__objects_14) \
#	libmemcached/libmemcached_libmemcached_la-allocators.lo \
#	libmemcached/libmemcached_libmemcached_la-analyze.lo \
#	libmemcached/libmemcached_libmemcached_la-array.lo \
#	libmemcached/libmemcached_libmemcached_la-auto.lo \
#	libmemcached/libmemcached_libmemcached_la-backtrace.lo \
#	libmemcached/libmemcached_libmemcached_la-behavior.lo \
#	libmemcached/libmemcached_libmemcached_la-byteorder.lo \
#	libmemcached/libmemcached_libmemcached_la-callback.lo \
#	libmemcached/libmemcached_libmemcached_la-connect.lo \
#	libmemcached/libmemcached_libmemcached_la-delete.lo \
#	libmemcached/libmemcached_libmemcached_la-do.lo \
#	libmemcached/libmemcached_libmemcached_la-dump.lo \
#	libmemcached/libmemcached_libmemcached_la-error.lo \
#	libmemcached/libmemcached_libmemcached_la-exist.lo \
#	libmemcached/libmemcached_libmemcached_la-fetch.lo \
#	libmemcached/libmemcached_libmemcached_la-flag.lo \
#	libmemcached/libmemcached_libmemcached_la-flush.lo \
#	libmemcached/libmemcached_libmemcached_la-flush_buffers.lo \
#	libmemcached/libmemcached_libmemcached_la-get.lo \
#	libmemcached/libmemcached_libmemcached_la-hash.lo \
#	libmemcached/libmemcached_libmemcached_la-hosts.lo \
#	libmemcached/libmemcached_libmemcached_la-initialize_query.lo \
#	libmemcached/libmemcached_libmemcached_la-io.lo \
#	libmemcached/libmemcached_libmemcached_la-key.lo \
#	libmemcached/libmemcached_libmemcached_la-memcached.lo \
#	libmemcached/libmemcached_libmemcached_la-encoding_key.lo \
#	libmemcached/libmemcached_libmemcached_la-namespace.lo \
#	libmemcached/libmemcached_libmemcached_la-options.lo \
#	libmemcached/libmemcached_libmemcached_la-parse.lo \
#	libmemcached/libmemcached_libmemcached_la-poll.lo \
#	libmemcached/libmemcached_libmemcached_la-purge.lo \
#	libmemcached/libmemcached_libmemcached_la-quit.lo \
#	libmemcached/libmemcached_libmemcached_la-response.lo \
#	libmemcached/libmemcached_libmemcached_la-result.lo \
#	libmemcached/libmemcached_libmemcached_la-sasl.lo \
#	libmemcached/libmemcached_libmemcached_la-server.lo \
#	libmemcached/libmemcached_libmemcached_la-server_list.lo \
#	libmemcached/libmemcached_libmemcached_la-stats.lo \
#	libmemcached/libmemcached_libmemcached_la-storage.lo \
#	libmemcached/libmemcached_libmemcached_la-strerror.lo \
#	libmemcached/libmemcached_libmemcached_la-string.lo \
#	libmemcached/libmemcached_libmemcached_la-touch.lo \
#	libmemcached/libmemcached_libmemcached_la-udp.lo \
#	libmemcached/libmemcached_libmemcached_la-verbosity.lo \
#	libmemcached/libmemcached_libmemcached_la-version.lo \
#	libmemcached/libmemcached_libmemcached_la-virtual_bucket.lo \
#	$(am__objects_15) $(am__objects_15)
libmemcached_libmemcached_la_OBJECTS =  \
	$(am_libmemcached_libmemcached_la_OBJECTS)
libmemcached_libmemcached_la_LINK = $(LIBTOOL) $(AM_V_lt) --tag=CXX \
	$(AM_LIBTOOLFLAGS) $(LIBTOOLFLAGS) --mode=link $(CXXLD) \
	$(libmemcached_libmemcached_la_CXXFLAGS) $(CXXFLAGS) \
	$(libmemcached_libmemcached_la_LDFLAGS) $(LDFLAGS) -o $@
am_libmemcached_libmemcached_la_rpath = -rpath \
	$(libdir)
#am_libmemcached_libmemcached_la_rpath = -rpath \
#	$(libdir)
libmemcached_libmemcachedprotocol_la_DEPENDENCIES =
am__libmemcached_libmemcachedprotocol_la_SOURCES_DIST =  \
	libmemcached/byteorder.cc libmemcachedprotocol/ascii_handler.c \
	libmemcachedprotocol/binary_handler.c \
	libmemcachedprotocol/cache.c libmemcachedprotocol/handler.c \
	libmemcachedprotocol/pedantic.c
#am_libmemcached_libmemcachedprotocol_la_OBJECTS = libmemcached/libmemcached_libmemcachedprotocol_la-byteorder.lo \
#	libmemcachedprotocol/libmemcached_libmemcachedprotocol_la-ascii_handler.lo \
#	libmemcachedprotocol/libmemcached_libmemcachedprotocol_la-binary_handler.lo \
#	libmemcachedprotocol/libmemcached_libmemcachedprotocol_la-cache.lo \
#	libmemcachedprotocol/libmemcached_libmemcachedprotocol_la-handler.lo \
#	libmemcachedprotocol/libmemcached_libmemcachedprotocol_la-pedantic.lo
libmemcached_libmemcachedprotocol_la_OBJECTS =  \
	$(am_libmemcached_libmemcachedprotocol_la_OBJECTS)
libmemcached_libmemcachedprotocol_la_LINK = $(LIBTOOL) $(AM_V_lt) \
	--tag=CXX $(AM_LIBTOOLFLAGS) $(LIBTOOLFLAGS) --mode=link \
	$(CXXLD) $(libmemcached_libmemcachedprotocol_la_CXXFLAGS) \
	$(CXXFLAGS) $(libmemcached_libmemcachedprotocol_la_LDFLAGS) \
	$(LDFLAGS) -o $@
#am_libmemcached_libmemcachedprotocol_la_rpath =  \
#	-rpath \
#	$(libdir)
libmemcached_libmemcachedutil_la_DEPENDENCIES =  \
	libmemcached/libmemcached.la
am__libmemcached_libmemcachedutil_la_SOURCES_DIST =  \
	libmemcached/backtrace.cc libmemcachedutil/flush.cc \
	libmemcachedutil/pid.cc libmemcachedutil/ping.cc \
	libmemcachedutil/pool.cc libmemcachedutil/version.cc
am_libmemcached_libmemcachedutil_la_OBJECTS = libmemcached/libmemcached_libmemcachedutil_la-backtrace.lo \
	libmemcachedutil/libmemcached_libmemcachedutil_la-flush.lo \
	libmemcachedutil/libmemcached_libmemcachedutil_la-pid.lo \
	libmemcachedutil/libmemcached_libmemcachedutil_la-ping.lo \
	libmemcachedutil/libmemcached_libmemcachedutil_la-pool.lo \
	libmemcachedutil/libmemcached_libmemcachedutil_la-version.lo
libmemcached_libmemcachedutil_la_OBJECTS =  \
	$(am_libmemcached_libmemcachedutil_la_OBJECTS)
libmemcached_libmemcachedutil_la_LINK = $(LIBTOOL) $(AM_V_lt) \
	--tag=CXX $(AM_LIBTOOLFLAGS) $(LIBTOOLFLAGS) --mode=link \
	$(CXXLD) $(libmemcached_libmemcachedutil_la_CXXFLAGS) \
	$(CXXFLAGS) $(libmemcached_libmemcachedutil_la_LDFLAGS) \
	$(LDFLAGS) -o $@
am_libmemcached_libmemcachedutil_la_rpath = -rpath \
	$(libdir)
am__DEPENDENCIES_2 = $(am__DEPENDENCIES_1) \
	$(am__append_59)
#am__DEPENDENCIES_2 = $(am__DEPENDENCIES_1) \
#	$(am__append_17) $(am__DEPENDENCIES_1) \
#	$(am__append_59)
libmemcachedinternal_libmemcachedinternal_la_DEPENDENCIES =  \
	$(am__DEPENDENCIES_2)
am__libmemcachedinternal_libmemcachedinternal_la_SOURCES_DIST =  \
	libmemcached/csl/context.cc libmemcached/csl/parser.cc \
	libmemcached/csl/scanner.cc libmemcached/instance.cc \
	libhashkit/aes.cc libhashkit/algorithm.cc \
	libhashkit/behavior.cc libhashkit/crc32.cc \
	libhashkit/digest.cc libhashkit/encrypt.cc \
	libhashkit/fnv_32.cc libhashkit/fnv_64.cc \
	libhashkit/function.cc libhashkit/has.cc libhashkit/hashkit.cc \
	libhashkit/jenkins.cc libhashkit/ketama.cc libhashkit/md5.cc \
	libhashkit/murmur.cc libhashkit/murmur3.cc \
	libhashkit/murmur3_api.cc libhashkit/one_at_a_time.cc \
	libhashkit/rijndael.cc libhashkit/str_algorithm.cc \
	libhashkit/strerror.cc libhashkit/string.cc \
	libhashkit/hsieh.cc libhashkit/nohsieh.cc \
	libmemcached/allocators.cc libmemcached/allocators.hpp \
	libmemcached/analyze.cc libmemcached/array.c \
	libmemcached/auto.cc libmemcached/backtrace.cc \
	libmemcached/behavior.cc libmemcached/byteorder.cc \
	libmemcached/callback.cc libmemcached/connect.cc \
	libmemcached/delete.cc libmemcached/do.cc libmemcached/dump.cc \
	libmemcached/error.cc libmemcached/exist.cc \
	libmemcached/fetch.cc libmemcached/flag.cc \
	libmemcached/flush.cc libmemcached/flush_buffers.cc \
	libmemcached/get.cc libmemcached/hash.cc libmemcached/hash.hpp \
	libmemcached/hosts.cc libmemcached/initialize_query.cc \
	libmemcached/io.cc libmemcached/key.cc \
	libmemcached/memcached.cc libmemcached/encoding_key.cc \
	libmemcached/namespace.cc libmemcached/options.cc \
	libmemcached/parse.cc libmemcached/poll.cc \
	libmemcached/purge.cc libmemcached/quit.cc \
	libmemcached/quit.hpp libmemcached/response.cc \
	libmemcached/result.cc libmemcached/sasl.cc \
	libmemcached/server.cc libmemcached/server_list.cc \
	libmemcached/server_list.hpp libmemcached/stats.cc \
	libmemcached/storage.cc libmemcached/strerror.cc \
	libmemcached/string.cc libmemcached/touch.cc \
	libmemcached/udp.cc libmemcached/verbosity.cc \
	libmemcached/version.cc libmemcached/virtual_bucket.c \
	libmemcached/libmemcached_probes.d
#am__objects_16 = libhashkit/libmemcachedinternal_libmemcachedinternal_la-hsieh.lo
am__objects_17 = libhashkit/libmemcachedinternal_libmemcachedinternal_la-nohsieh.lo
##am__objects_18 = libhashkit/libmemcachedinternal_libmemcachedinternal_la-hsieh.lo
#am__objects_19 = libhashkit/libmemcachedinternal_libmemcachedinternal_la-nohsieh.lo
am__objects_20 = libhashkit/libmemcachedinternal_libmemcachedinternal_la-aes.lo \
	libhashkit/libmemcachedinternal_libmemcachedinternal_la-algorithm.lo \
	libhashkit/libmemcachedinternal_libmemcachedinternal_la-behavior.lo \
	libhashkit/libmemcachedinternal_libmemcachedinternal_la-crc32.lo \
	libhashkit/libmemcachedinternal_libmemcachedinternal_la-digest.lo \
	libhashkit/libmemcachedinternal_libmemcachedinternal_la-encrypt.lo \
	libhashkit/libmemcachedinternal_libmemcachedinternal_la-fnv_32.lo \
	libhashkit/libmemcachedinternal_libmemcachedinternal_la-fnv_64.lo \
	libhashkit/libmemcachedinternal_libmemcachedinternal_la-function.lo \
	libhashkit/libmemcachedinternal_libmemcachedinternal_la-has.lo \
	libhashkit/libmemcachedinternal_libmemcachedinternal_la-hashkit.lo \
	libhashkit/libmemcachedinternal_libmemcachedinternal_la-jenkins.lo \
	libhashkit/libmemcachedinternal_libmemcachedinternal_la-ketama.lo \
	libhashkit/libmemcachedinternal_libmemcachedinternal_la-md5.lo \
	libhashkit/libmemcachedinternal_libmemcachedinternal_la-murmur.lo \
	libhashkit/libmemcachedinternal_libmemcachedinternal_la-murmur3.lo \
	libhashkit/libmemcachedinternal_libmemcachedinternal_la-murmur3_api.lo \
	libhashkit/libmemcachedinternal_libmemcachedinternal_la-one_at_a_time.lo \
	libhashkit/libmemcachedinternal_libmemcachedinternal_la-rijndael.lo \
	libhashkit/libmemcachedinternal_libmemcachedinternal_la-str_algorithm.lo \
	libhashkit/libmemcachedinternal_libmemcachedinternal_la-strerror.lo \
	libhashkit/libmemcachedinternal_libmemcachedinternal_la-string.lo \
	$(am__objects_16) $(am__objects_17)
#am__objects_20 = libhashkit/libmemcachedinternal_libmemcachedinternal_la-aes.lo \
#	libhashkit/libmemcachedinternal_libmemcachedinternal_la-algorithm.lo \
#	libhashkit/libmemcachedinternal_libmemcachedinternal_la-behavior.lo \
#	libhashkit/libmemcachedinternal_libmemcachedinternal_la-crc32.lo \
#	libhashkit/libmemcachedinternal_libmemcachedinternal_la-digest.lo \
#	libhashkit/libmemcachedinternal_libmemcachedinternal_la-encrypt.lo \
#	libhashkit/libmemcachedinternal_libmemcachedinternal_la-fnv_32.lo \
#	libhashkit/libmemcachedinternal_libmemcachedinternal_la-fnv_64.lo \
#	libhashkit/libmemcachedinternal_libmemcachedinternal_la-function.lo \
#	libhashkit/libmemcachedinternal_libmemcachedinternal_la-has.lo \
#	libhashkit/libmemcachedinternal_libmemcachedinternal_la-hashkit.lo \
#	libhashkit/libmemcachedinternal_libmemcachedinternal_la-jenkins.lo \
#	libhashkit/libmemcachedinternal_libmemcachedinternal_la-ketama.lo \
#	libhashkit/libmemcachedinternal_libmemcachedinternal_la-md5.lo \
#	libhashkit/libmemcachedinternal_libmemcachedinternal_la-murmur.lo \
#	libhashkit/libmemcachedinternal_libmemcachedinternal_la-murmur3.lo \
#	libhashkit/libmemcachedinternal_libmemcachedinternal_la-murmur3_api.lo \
#	libhashkit/libmemcachedinternal_libmemcachedinternal_la-one_at_a_time.lo \
#	libhashkit/libmemcachedinternal_libmemcachedinternal_la-rijndael.lo \
#	libhashkit/libmemcachedinternal_libmemcachedinternal_la-str_algorithm.lo \
#	libhashkit/libmemcachedinternal_libmemcachedinternal_la-strerror.lo \
#	libhashkit/libmemcachedinternal_libmemcachedinternal_la-string.lo \
#	$(am__objects_18) $(am__objects_19) \
#	$(am__objects_16) $(am__objects_17)
am__objects_21 = libmemcached/csl/libmemcachedinternal_libmemcachedinternal_la-context.lo \
	libmemcached/csl/libmemcachedinternal_libmemcachedinternal_la-parser.lo \
	libmemcached/csl/libmemcachedinternal_libmemcachedinternal_la-scanner.lo \
	libmemcached/libmemcachedinternal_libmemcachedinternal_la-instance.lo \
	$(am__objects_20) \
	libmemcached/libmemcachedinternal_libmemcachedinternal_la-allocators.lo \
	libmemcached/libmemcachedinternal_libmemcachedinternal_la-analyze.lo \
	libmemcached/libmemcachedinternal_libmemcachedinternal_la-array.lo \
	libmemcached/libmemcachedinternal_libmemcachedinternal_la-auto.lo \
	libmemcached/libmemcachedinternal_libmemcachedinternal_la-backtrace.lo \
	libmemcached/libmemcachedinternal_libmemcachedinternal_la-behavior.lo \
	libmemcached/libmemcachedinternal_libmemcachedinternal_la-byteorder.lo \
	libmemcached/libmemcachedinternal_libmemcachedinternal_la-callback.lo \
	libmemcached/libmemcachedinternal_libmemcachedinternal_la-connect.lo \
	libmemcached/libmemcachedinternal_libmemcachedinternal_la-delete.lo \
	libmemcached/libmemcachedinternal_libmemcachedinternal_la-do.lo \
	libmemcached/libmemcachedinternal_libmemcachedinternal_la-dump.lo \
	libmemcached/libmemcachedinternal_libmemcachedinternal_la-error.lo \
	libmemcached/libmemcachedinternal_libmemcachedinternal_la-exist.lo \
	libmemcached/libmemcachedinternal_libmemcachedinternal_la-fetch.lo \
	libmemcached/libmemcachedinternal_libmemcachedinternal_la-flag.lo \
	libmemcached/libmemcachedinternal_libmemcachedinternal_la-flush.lo \
	libmemcached/libmemcachedinternal_libmemcachedinternal_la-flush_buffers.lo \
	libmemcached/libmemcachedinternal_libmemcachedinternal_la-get.lo \
	libmemcached/libmemcachedinternal_libmemcachedinternal_la-hash.lo \
	libmemcached/libmemcachedinternal_libmemcachedinternal_la-hosts.lo \
	libmemcached/libmemcachedinternal_libmemcachedinternal_la-initialize_query.lo \
	libmemcached/libmemcachedinternal_libmemcachedinternal_la-io.lo \
	libmemcached/libmemcachedinternal_libmemcachedinternal_la-key.lo \
	libmemcached/libmemcachedinternal_libmemcachedinternal_la-memcached.lo \
	libmemcached/libmemcachedinternal_libmemcachedinternal_la-encoding_key.lo \
	libmemcached/libmemcachedinternal_libmemcachedinternal_la-namespace.lo \
	libmemcached/libmemcachedinternal_libmemcachedinternal_la-options.lo \
	libmemcached/libmemcachedinternal_libmemcachedinternal_la-parse.lo \
	libmemcached/libmemcachedinternal_libmemcachedinternal_la-poll.lo \
	libmemcached/libmemcachedinternal_libmemcachedinternal_la-purge.lo \
	libmemcached/libmemcachedinternal_libmemcachedinternal_la-quit.lo \
	libmemcached/libmemcachedinternal_libmemcachedinternal_la-response.lo \
	libmemcached/libmemcachedinternal_libmemcachedinternal_la-result.lo \
	libmemcached/libmemcachedinternal_libmemcachedinternal_la-sasl.lo \
	libmemcached/libmemcachedinternal_libmemcachedinternal_la-server.lo \
	libmemcached/libmemcachedinternal_libmemcachedinternal_la-server_list.lo \
	libmemcached/libmemcachedinternal_libmemcachedinternal_la-stats.lo \
	libmemcached/libmemcachedinternal_libmemcachedinternal_la-storage.lo \
	libmemcached/libmemcachedinternal_libmemcachedinternal_la-strerror.lo \
	libmemcached/libmemcachedinternal_libmemcachedinternal_la-string.lo \
	libmemcached/libmemcachedinternal_libmemcachedinternal_la-touch.lo \
	libmemcached/libmemcachedinternal_libmemcachedinternal_la-udp.lo \
	libmemcached/libmemcachedinternal_libmemcachedinternal_la-verbosity.lo \
	libmemcached/libmemcachedinternal_libmemcachedinternal_la-version.lo \
	libmemcached/libmemcachedinternal_libmemcachedinternal_la-virtual_bucket.lo \
	$(am__objects_15)
#am__objects_21 = libmemcached/csl/libmemcachedinternal_libmemcachedinternal_la-context.lo \
#	libmemcached/csl/libmemcachedinternal_libmemcachedinternal_la-parser.lo \
#	libmemcached/csl/libmemcachedinternal_libmemcachedinternal_la-scanner.lo \
#	libmemcached/libmemcachedinternal_libmemcachedinternal_la-instance.lo \
#	$(am__objects_20) \
#	libmemcached/libmemcachedinternal_libmemcachedinternal_la-allocators.lo \
#	libmemcached/libmemcachedinternal_libmemcachedinternal_la-analyze.lo \
#	libmemcached/libmemcachedinternal_libmemcachedinternal_la-array.lo \
#	libmemcached/libmemcachedinternal_libmemcachedinternal_la-auto.lo \
#	libmemcached/libmemcachedinternal_libmemcachedinternal_la-backtrace.lo \
#	libmemcached/libmemcachedinternal_libmemcachedinternal_la-behavior.lo \
#	libmemcached/libmemcachedinternal_libmemcachedinternal_la-byteorder.lo \
#	libmemcached/libmemcachedinternal_libmemcachedinternal_la-callback.lo \
#	libmemcached/libmemcachedinternal_libmemcachedinternal_la-connect.lo \
#	libmemcached/libmemcachedinternal_libmemcachedinternal_la-delete.lo \
#	libmemcached/libmemcachedinternal_libmemcachedinternal_la-do.lo \
#	libmemcached/libmemcachedinternal_libmemcachedinternal_la-dump.lo \
#	libmemcached/libmemcachedinternal_libmemcachedinternal_la-error.lo \
#	libmemcached/libmemcachedinternal_libmemcachedinternal_la-exist.lo \
#	libmemcached/libmemcachedinternal_libmemcachedinternal_la-fetch.lo \
#	libmemcached/libmemcachedinternal_libmemcachedinternal_la-flag.lo \
#	libmemcached/libmemcachedinternal_libmemcachedinternal_la-flush.lo \
#	libmemcached/libmemcachedinternal_libmemcachedinternal_la-flush_buffers.lo \
#	libmemcached/libmemcachedinternal_libmemcachedinternal_la-get.lo \
#	libmemcached/libmemcachedinternal_libmemcachedinternal_la-hash.lo \
#	libmemcached/libmemcachedinternal_libmemcachedinternal_la-hosts.lo \
#	libmemcached/libmemcachedinternal_libmemcachedinternal_la-initialize_query.lo \
#	libmemcached/libmemcachedinternal_libmemcachedinternal_la-io.lo \
#	libmemcached/libmemcachedinternal_libmemcachedinternal_la-key.lo \
#	libmemcached/libmemcachedinternal_libmemcachedinternal_la-memcached.lo \
#	libmemcached/libmemcachedinternal_libmemcachedinternal_la-encoding_key.lo \
#	libmemcached/libmemcachedinternal_libmemcachedinternal_la-namespace.lo \
#	libmemcached/libmemcachedinternal_libmemcachedinternal_la-options.lo \
#	libmemcached/libmemcachedinternal_libmemcachedinternal_la-parse.lo \
#	libmemcached/libmemcachedinternal_libmemcachedinternal_la-poll.lo \
#	libmemcached/libmemcachedinternal_libmemcachedinternal_la-purge.lo \
#	libmemcached/libmemcachedinternal_libmemcachedinternal_la-quit.lo \
#	libmemcached/libmemcachedinternal_libmemcachedinternal_la-response.lo \
#	libmemcached/libmemcachedinternal_libmemcachedinternal_la-result.lo \
#	libmemcached/libmemcachedinternal_libmemcachedinternal_la-sasl.lo \
#	libmemcached/libmemcachedinternal_libmemcachedinternal_la-server.lo \
#	libmemcached/libmemcachedinternal_libmemcachedinternal_la-server_list.lo \
#	libmemcached/libmemcachedinternal_libmemcachedinternal_la-stats.lo \
#	libmemcached/libmemcachedinternal_libmemcachedinternal_la-storage.lo \
#	libmemcached/libmemcachedinternal_libmemcachedinternal_la-strerror.lo \
#	libmemcached/libmemcachedinternal_libmemcachedinternal_la-string.lo \
#	libmemcached/libmemcachedinternal_libmemcachedinternal_la-touch.lo \
#	libmemcached/libmemcachedinternal_libmemcachedinternal_la-udp.lo \
#	libmemcached/libmemcachedinternal_libmemcachedinternal_la-verbosity.lo \
#	libmemcached/libmemcachedinternal_libmemcachedinternal_la-version.lo \
#	libmemcached/libmemcachedinternal_libmemcachedinternal_la-virtual_bucket.lo \
#	$(am__objects_15) $(am__objects_15)
am_libmemcachedinternal_libmemcachedinternal_la_OBJECTS =  \
	$(am__objects_21)
libmemcachedinternal_libmemcachedinternal_la_OBJECTS =  \
	$(am_libmemcachedinternal_libmemcachedinternal_la_OBJECTS)
libmemcachedinternal_libmemcachedinternal_la_LINK = $(LIBTOOL) \
	$(AM_V_lt) --tag=CXX $(AM_LIBTOOLFLAGS) $(LIBTOOLFLAGS) \
	--mode=link $(CXXLD) \
	$(libmemcachedinternal_libmemcachedinternal_la_CXXFLAGS) \
	$(CXXFLAGS) $(AM_LDFLAGS) $(LDFLAGS) -o $@
am_libmemcachedinternal_libmemcachedinternal_la_rpath =
libmemcachedinternal_libmemcachedutilinternal_la_DEPENDENCIES = libmemcachedinternal/libmemcachedinternal.la
am__libmemcachedinternal_libmemcachedutilinternal_la_SOURCES_DIST =  \
	libmemcached/backtrace.cc libmemcachedutil/flush.cc \
	libmemcachedutil/pid.cc libmemcachedutil/ping.cc \
	libmemcachedutil/pool.cc libmemcachedutil/version.cc
am__objects_22 = libmemcached/libmemcachedinternal_libmemcachedutilinternal_la-backtrace.lo \
	libmemcachedutil/libmemcachedinternal_libmemcachedutilinternal_la-flush.lo \
	libmemcachedutil/libmemcachedinternal_libmemcachedutilinternal_la-pid.lo \
	libmemcachedutil/libmemcachedinternal_libmemcachedutilinternal_la-ping.lo \
	libmemcachedutil/libmemcachedinternal_libmemcachedutilinternal_la-pool.lo \
	libmemcachedutil/libmemcachedinternal_libmemcachedutilinternal_la-version.lo
am_libmemcachedinternal_libmemcachedutilinternal_la_OBJECTS =  \
	$(am__objects_22)
libmemcachedinternal_libmemcachedutilinternal_la_OBJECTS = $(am_libmemcachedinternal_libmemcachedutilinternal_la_OBJECTS)
libmemcachedinternal_libmemcachedutilinternal_la_LINK = $(LIBTOOL) \
	$(AM_V_lt) --tag=CXX $(AM_LIBTOOLFLAGS) $(LIBTOOLFLAGS) \
	--mode=link $(CXXLD) \
	$(libmemcachedinternal_libmemcachedutilinternal_la_CXXFLAGS) \
	$(CXXFLAGS) $(AM_LDFLAGS) $(LDFLAGS) -o $@
am_libmemcachedinternal_libmemcachedutilinternal_la_rpath =
libtest_libtest_la_DEPENDENCIES =  \
	$(am__DEPENDENCIES_1)
am__libtest_libtest_la_SOURCES_DIST = libtest/alarm.cc \
	libtest/binaries.cc libtest/cmdline.cc libtest/collection.cc \
	libtest/comparison.cc libtest/core.cc libtest/cpu.cc \
	libtest/dns.cc libtest/dream.cc libtest/drizzled.cc \
	libtest/exception.cc libtest/exception/fatal.cc \
	libtest/formatter.cc libtest/client.cc libtest/framework.cc \
	libtest/has.cc libtest/http.cc libtest/is_local.cc \
	libtest/killpid.cc libtest/libtool.cc libtest/main.cc \
	libtest/port.cc libtest/result.cc libtest/runner.cc \
	libtest/server.cc libtest/server_container.cc \
	libtest/signal.cc libtest/socket.cc libtest/strerror.cc \
	libtest/timer.cc libtest/tmpfile.cc libtest/vchar.cc \
	libtest/memcached.cc libtest/gearmand.cc \
	libtest/blobslap_worker.cc
#am__objects_23 = libtest/libtest_libtest_la-blobslap_worker.lo
am_libtest_libtest_la_OBJECTS =  \
	libtest/libtest_libtest_la-alarm.lo \
	libtest/libtest_libtest_la-binaries.lo \
	libtest/libtest_libtest_la-cmdline.lo \
	libtest/libtest_libtest_la-collection.lo \
	libtest/libtest_libtest_la-comparison.lo \
	libtest/libtest_libtest_la-core.lo \
	libtest/libtest_libtest_la-cpu.lo \
	libtest/libtest_libtest_la-dns.lo \
	libtest/libtest_libtest_la-dream.lo \
	libtest/libtest_libtest_la-drizzled.lo \
	libtest/libtest_libtest_la-exception.lo \
	libtest/exception/libtest_libtest_la-fatal.lo \
	libtest/libtest_libtest_la-formatter.lo \
	libtest/libtest_libtest_la-client.lo \
	libtest/libtest_libtest_la-framework.lo \
	libtest/libtest_libtest_la-has.lo \
	libtest/libtest_libtest_la-http.lo \
	libtest/libtest_libtest_la-is_local.lo \
	libtest/libtest_libtest_la-killpid.lo \
	libtest/libtest_libtest_la-libtool.lo \
	libtest/libtest_libtest_la-main.lo \
	libtest/libtest_libtest_la-port.lo \
	libtest/libtest_libtest_la-result.lo \
	libtest/libtest_libtest_la-runner.lo \
	libtest/libtest_libtest_la-server.lo \
	libtest/libtest_libtest_la-server_container.lo \
	libtest/libtest_libtest_la-signal.lo \
	libtest/libtest_libtest_la-socket.lo \
	libtest/libtest_libtest_la-strerror.lo \
	libtest/libtest_libtest_la-timer.lo \
	libtest/libtest_libtest_la-tmpfile.lo \
	libtest/libtest_libtest_la-vchar.lo \
	libtest/libtest_libtest_la-memcached.lo \
	libtest/libtest_libtest_la-gearmand.lo \
	$(am__objects_23)
libtest_libtest_la_OBJECTS = $(am_libtest_libtest_la_OBJECTS)
libtest_libtest_la_LINK = $(LIBTOOL) $(AM_V_lt) --tag=CXX \
	$(AM_LIBTOOLFLAGS) $(LIBTOOLFLAGS) --mode=link $(CXXLD) \
	$(libtest_libtest_la_CXXFLAGS) $(CXXFLAGS) \
	$(libtest_libtest_la_LDFLAGS) $(LDFLAGS) -o $@
am_libtest_libtest_la_rpath =
am__EXEEXT_1 = clients/memcapable$(EXEEXT) \
	clients/memcat$(EXEEXT) \
	clients/memcp$(EXEEXT) \
	clients/memdump$(EXEEXT) \
	clients/memerror$(EXEEXT) \
	clients/memexist$(EXEEXT) \
	clients/memtouch$(EXEEXT) \
	clients/memflush$(EXEEXT) \
	clients/memparse$(EXEEXT) \
	clients/memping$(EXEEXT) \
	clients/memrm$(EXEEXT) \
	clients/memslap$(EXEEXT) \
	clients/memstat$(EXEEXT)
am__EXEEXT_2 = clients/memaslap$(EXEEXT)
#am__EXEEXT_3 = libmemcached-1.0/t/c_test$(EXEEXT) \
#	libmemcached-1.0/t/c_sasl_test$(EXEEXT)
#am__EXEEXT_4 = libmemcached-1.0/t/cc_test$(EXEEXT)
am__EXEEXT_5 = libtest/unittest$(EXEEXT) \
	libtest/skiptest$(EXEEXT)
am__EXEEXT_6 = libmemcached-1.0/t/c_test$(EXEEXT) \
	libmemcached-1.0/t/c_sasl_test$(EXEEXT)
am__EXEEXT_7 = libmemcached-1.0/t/cc_test$(EXEEXT) \
	tests/cycle$(EXEEXT)
am__EXEEXT_8 = tests/libmemcached-1.0/internals$(EXEEXT)
am__EXEEXT_9 =  \
	tests/libmemcached-1.0/testapp$(EXEEXT) \
	tests/libmemcached-1.0/testsocket$(EXEEXT) \
	tests/libmemcached-1.0/sasl$(EXEEXT) \
	tests/testudp$(EXEEXT) \
	tests/testplus$(EXEEXT) \
	tests/parser$(EXEEXT) \
	tests/failure$(EXEEXT) \
	tests/testhashkit$(EXEEXT) \
	tests/hash_plus$(EXEEXT) \
	tests/memcapable$(EXEEXT) \
	tests/memstat$(EXEEXT) tests/memcp$(EXEEXT) \
	tests/memflush$(EXEEXT) \
	tests/memrm$(EXEEXT) \
	tests/memexist$(EXEEXT) \
	tests/memtouch$(EXEEXT) \
	tests/memcat$(EXEEXT) \
	tests/memping$(EXEEXT) \
	tests/memerror$(EXEEXT) \
	tests/memslap$(EXEEXT) \
	tests/memdump$(EXEEXT)
am__EXEEXT_10 = libtest/unittest$(EXEEXT) \
	libtest/skiptest$(EXEEXT) \
	libtest/wait$(EXEEXT) \
	libtest/core-count$(EXEEXT) \
	libtest/abort$(EXEEXT) \
	libtest/backtrace$(EXEEXT)
am__EXEEXT_11 =  \
	libmemcached-1.0/t/cc_test$(EXEEXT)
#am__EXEEXT_12 = example/memcached_light$(EXEEXT)
am__EXEEXT_13 = tests/cycle$(EXEEXT)
am__EXEEXT_14 =  \
	tests/libmemcached-1.0/testapp$(EXEEXT) \
	tests/libmemcached-1.0/testsocket$(EXEEXT) \
	tests/libmemcached-1.0/sasl$(EXEEXT) \
	tests/atomsmasher$(EXEEXT) \
	tests/testudp$(EXEEXT) \
	tests/testplus$(EXEEXT) \
	tests/parser$(EXEEXT) \
	tests/failure$(EXEEXT) \
	tests/testhashkit$(EXEEXT) \
	tests/hash_plus$(EXEEXT) \
	tests/memcapable$(EXEEXT) \
	tests/memstat$(EXEEXT) tests/memcp$(EXEEXT) \
	tests/memflush$(EXEEXT) \
	tests/memrm$(EXEEXT) \
	tests/memexist$(EXEEXT) \
	tests/memtouch$(EXEEXT) \
	tests/memcat$(EXEEXT) \
	tests/memping$(EXEEXT) \
	tests/memerror$(EXEEXT) \
	tests/memslap$(EXEEXT) \
	tests/memdump$(EXEEXT)
PROGRAMS = $(bin_PROGRAMS) $(noinst_PROGRAMS)
am__clients_memaslap_SOURCES_DIST = clients/memaslap.cc \
	clients/ms_conn.cc clients/ms_setting.cc clients/ms_sigsegv.cc \
	clients/ms_stats.cc clients/ms_task.cc clients/ms_thread.cc \
	clients/generator.cc clients/execute.cc
am_clients_memaslap_OBJECTS =  \
	clients/memaslap.$(OBJEXT) \
	clients/ms_conn.$(OBJEXT) \
	clients/ms_setting.$(OBJEXT) \
	clients/ms_sigsegv.$(OBJEXT) \
	clients/ms_stats.$(OBJEXT) \
	clients/ms_task.$(OBJEXT) \
	clients/ms_thread.$(OBJEXT) \
	clients/generator.$(OBJEXT) \
	clients/execute.$(OBJEXT)
clients_memaslap_OBJECTS = $(am_clients_memaslap_OBJECTS)
clients_memaslap_DEPENDENCIES = $(CLIENTS_LDADDS)
am__clients_memcapable_SOURCES_DIST = clients/memcapable.cc \
	libmemcached/byteorder.cc
am_clients_memcapable_OBJECTS = clients/clients_memcapable-memcapable.$(OBJEXT) \
	libmemcached/clients_memcapable-byteorder.$(OBJEXT)
clients_memcapable_OBJECTS = $(am_clients_memcapable_OBJECTS)
clients_memcapable_DEPENDENCIES =  \
	$(CLIENTS_LDADDS)
clients_memcapable_LINK = $(LIBTOOL) $(AM_V_lt) --tag=CXX \
	$(AM_LIBTOOLFLAGS) $(LIBTOOLFLAGS) --mode=link $(CXXLD) \
	$(clients_memcapable_CXXFLAGS) $(CXXFLAGS) $(AM_LDFLAGS) \
	$(LDFLAGS) -o $@
am__clients_memcat_SOURCES_DIST = clients/memcat.cc
am_clients_memcat_OBJECTS =  \
	clients/memcat.$(OBJEXT)
clients_memcat_OBJECTS = $(am_clients_memcat_OBJECTS)
clients_memcat_DEPENDENCIES = $(CLIENTS_LDADDS)
am__clients_memcp_SOURCES_DIST = clients/memcp.cc
am_clients_memcp_OBJECTS = clients/memcp.$(OBJEXT)
clients_memcp_OBJECTS = $(am_clients_memcp_OBJECTS)
clients_memcp_DEPENDENCIES = $(CLIENTS_LDADDS)
am__clients_memdump_SOURCES_DIST = clients/memdump.cc
am_clients_memdump_OBJECTS =  \
	clients/memdump.$(OBJEXT)
clients_memdump_OBJECTS = $(am_clients_memdump_OBJECTS)
clients_memdump_DEPENDENCIES = $(CLIENTS_LDADDS)
am__clients_memerror_SOURCES_DIST = clients/memerror.cc
am_clients_memerror_OBJECTS =  \
	clients/memerror.$(OBJEXT)
clients_memerror_OBJECTS = $(am_clients_memerror_OBJECTS)
clients_memerror_DEPENDENCIES = $(CLIENTS_LDADDS)
am__clients_memexist_SOURCES_DIST = clients/memexist.cc
am_clients_memexist_OBJECTS =  \
	clients/memexist.$(OBJEXT)
clients_memexist_OBJECTS = $(am_clients_memexist_OBJECTS)
clients_memexist_DEPENDENCIES = $(CLIENTS_LDADDS)
am__clients_memflush_SOURCES_DIST = clients/memflush.cc
am_clients_memflush_OBJECTS =  \
	clients/memflush.$(OBJEXT)
clients_memflush_OBJECTS = $(am_clients_memflush_OBJECTS)
clients_memflush_DEPENDENCIES = $(CLIENTS_LDADDS)
am__clients_memparse_SOURCES_DIST = clients/memparse.cc
am_clients_memparse_OBJECTS =  \
	clients/memparse.$(OBJEXT)
clients_memparse_OBJECTS = $(am_clients_memparse_OBJECTS)
clients_memparse_DEPENDENCIES = $(CLIENTS_LDADDS)
am__clients_memping_SOURCES_DIST = clients/memping.cc
am_clients_memping_OBJECTS =  \
	clients/memping.$(OBJEXT)
clients_memping_OBJECTS = $(am_clients_memping_OBJECTS)
clients_memping_DEPENDENCIES = $(CLIENTS_LDADDS) \
	libmemcached/libmemcachedutil.la
am__clients_memrm_SOURCES_DIST = clients/memrm.cc
am_clients_memrm_OBJECTS = clients/memrm.$(OBJEXT)
clients_memrm_OBJECTS = $(am_clients_memrm_OBJECTS)
clients_memrm_DEPENDENCIES = $(CLIENTS_LDADDS)
am__clients_memslap_SOURCES_DIST = clients/memslap.cc \
	clients/generator.cc clients/execute.cc
am_clients_memslap_OBJECTS =  \
	clients/clients_memslap-memslap.$(OBJEXT) \
	clients/clients_memslap-generator.$(OBJEXT) \
	clients/clients_memslap-execute.$(OBJEXT)
clients_memslap_OBJECTS = $(am_clients_memslap_OBJECTS)
clients_memslap_DEPENDENCIES = $(CLIENTS_LDADDS)
clients_memslap_LINK = $(LIBTOOL) $(AM_V_lt) --tag=CXX \
	$(AM_LIBTOOLFLAGS) $(LIBTOOLFLAGS) --mode=link $(CXXLD) \
	$(clients_memslap_CXXFLAGS) $(CXXFLAGS) $(AM_LDFLAGS) \
	$(LDFLAGS) -o $@
am__clients_memstat_SOURCES_DIST = clients/memstat.cc
am_clients_memstat_OBJECTS =  \
	clients/memstat.$(OBJEXT)
clients_memstat_OBJECTS = $(am_clients_memstat_OBJECTS)
clients_memstat_DEPENDENCIES = $(CLIENTS_LDADDS)
am__clients_memtouch_SOURCES_DIST = clients/memtouch.cc
am_clients_memtouch_OBJECTS =  \
	clients/memtouch.$(OBJEXT)
clients_memtouch_OBJECTS = $(am_clients_memtouch_OBJECTS)
clients_memtouch_DEPENDENCIES = $(CLIENTS_LDADDS)
am__example_memcached_light_SOURCES_DIST = example/byteorder.cc \
	example/interface_v0.cc example/interface_v1.cc \
	example/memcached_light.cc example/storage.cc util/daemon.cc \
	util/pidfile.cc
#am_example_memcached_light_OBJECTS = example/byteorder.$(OBJEXT) \
#	example/interface_v0.$(OBJEXT) \
#	example/interface_v1.$(OBJEXT) \
#	example/memcached_light.$(OBJEXT) \
#	example/storage.$(OBJEXT) \
#	util/daemon.$(OBJEXT) \
#	util/pidfile.$(OBJEXT)
example_memcached_light_OBJECTS =  \
	$(am_example_memcached_light_OBJECTS)
#example_memcached_light_DEPENDENCIES = libmemcached/libmemcachedprotocol.la
example_memcached_light_LINK = $(LIBTOOL) $(AM_V_lt) --tag=CXX \
	$(AM_LIBTOOLFLAGS) $(LIBTOOLFLAGS) --mode=link $(CXXLD) \
	$(AM_CXXFLAGS) $(CXXFLAGS) $(example_memcached_light_LDFLAGS) \
	$(LDFLAGS) -o $@
am__libmemcached_1_0_t_c_sasl_test_SOURCES_DIST =  \
	libmemcached-1.0/t/c_sasl_test.c
am_libmemcached_1_0_t_c_sasl_test_OBJECTS = libmemcached-1.0/t/c_sasl_test.$(OBJEXT)
#am_libmemcached_1_0_t_c_sasl_test_OBJECTS = libmemcached-1.0/t/c_sasl_test.$(OBJEXT)
libmemcached_1_0_t_c_sasl_test_OBJECTS =  \
	$(am_libmemcached_1_0_t_c_sasl_test_OBJECTS)
libmemcached_1_0_t_c_sasl_test_DEPENDENCIES = libmemcached/libmemcached.la
#libmemcached_1_0_t_c_sasl_test_DEPENDENCIES = libmemcached/libmemcached.la
am__libmemcached_1_0_t_c_test_SOURCES_DIST =  \
	libmemcached-1.0/t/c_test.c
am_libmemcached_1_0_t_c_test_OBJECTS = libmemcached-1.0/t/c_test.$(OBJEXT)
#am_libmemcached_1_0_t_c_test_OBJECTS = libmemcached-1.0/t/c_test.$(OBJEXT)
libmemcached_1_0_t_c_test_OBJECTS =  \
	$(am_libmemcached_1_0_t_c_test_OBJECTS)
libmemcached_1_0_t_c_test_DEPENDENCIES = libmemcached/libmemcached.la
#libmemcached_1_0_t_c_test_DEPENDENCIES = libmemcached/libmemcached.la
am__libmemcached_1_0_t_cc_test_SOURCES_DIST =  \
	libmemcached-1.0/t/cc_test.cc
am_libmemcached_1_0_t_cc_test_OBJECTS =  \
	libmemcached-1.0/t/cc_test.$(OBJEXT)
#am_libmemcached_1_0_t_cc_test_OBJECTS =  \
#	libmemcached-1.0/t/cc_test.$(OBJEXT)
libmemcached_1_0_t_cc_test_OBJECTS =  \
	$(am_libmemcached_1_0_t_cc_test_OBJECTS)
libmemcached_1_0_t_cc_test_DEPENDENCIES =  \
	libmemcached/libmemcached.la
#libmemcached_1_0_t_cc_test_DEPENDENCIES =  \
#	libmemcached/libmemcached.la
am__libtest_abort_SOURCES_DIST = libtest/abort.cc
am_libtest_abort_OBJECTS = libtest/abort.$(OBJEXT)
libtest_abort_OBJECTS = $(am_libtest_abort_OBJECTS)
libtest_abort_LDADD = $(LDADD)
am__libtest_backtrace_SOURCES_DIST = libtest/backtrace_test.cc \
	libmemcached/backtrace.cc
am_libtest_backtrace_OBJECTS =  \
	libtest/backtrace_test.$(OBJEXT) \
	libmemcached/backtrace.$(OBJEXT)
libtest_backtrace_OBJECTS = $(am_libtest_backtrace_OBJECTS)
libtest_backtrace_DEPENDENCIES =
am__libtest_core_count_SOURCES_DIST = libtest/cpu.cc \
	libtest/core_count.cc
am_libtest_core_count_OBJECTS =  \
	libtest/cpu.$(OBJEXT) \
	libtest/core_count.$(OBJEXT)
libtest_core_count_OBJECTS = $(am_libtest_core_count_OBJECTS)
libtest_core_count_LDADD = $(LDADD)
am__libtest_skiptest_SOURCES_DIST = libtest/skiptest.cc
am_libtest_skiptest_OBJECTS =  \
	libtest/skiptest.$(OBJEXT)
libtest_skiptest_OBJECTS = $(am_libtest_skiptest_OBJECTS)
libtest_skiptest_DEPENDENCIES = libtest/libtest.la
am__libtest_unittest_SOURCES_DIST = libtest/unittest.cc
am_libtest_unittest_OBJECTS = libtest/libtest_unittest-unittest.$(OBJEXT)
libtest_unittest_OBJECTS = $(am_libtest_unittest_OBJECTS)
libtest_unittest_DEPENDENCIES = libtest/libtest.la
libtest_unittest_LINK = $(LIBTOOL) $(AM_V_lt) --tag=CXX \
	$(AM_LIBTOOLFLAGS) $(LIBTOOLFLAGS) --mode=link $(CXXLD) \
	$(libtest_unittest_CXXFLAGS) $(CXXFLAGS) $(AM_LDFLAGS) \
	$(LDFLAGS) -o $@
am__libtest_wait_SOURCES_DIST = libtest/wait.cc libtest/dream.cc
am_libtest_wait_OBJECTS = libtest/wait.$(OBJEXT) \
	libtest/dream.$(OBJEXT)
libtest_wait_OBJECTS = $(am_libtest_wait_OBJECTS)
libtest_wait_LDADD = $(LDADD)
am__tests_atomsmasher_SOURCES_DIST = clients/execute.cc \
	clients/generator.cc tests/libmemcached-1.0/atomsmasher.cc \
	tests/libmemcached-1.0/callback_counter.cc \
	tests/libmemcached-1.0/debug.cc \
	tests/libmemcached-1.0/fetch_all_results.cc \
	tests/libmemcached-1.0/generate.cc \
	tests/libmemcached-1.0/print.cc
am_tests_atomsmasher_OBJECTS =  \
	clients/execute.$(OBJEXT) \
	clients/generator.$(OBJEXT) \
	tests/libmemcached-1.0/atomsmasher.$(OBJEXT) \
	tests/libmemcached-1.0/callback_counter.$(OBJEXT) \
	tests/libmemcached-1.0/debug.$(OBJEXT) \
	tests/libmemcached-1.0/fetch_all_results.$(OBJEXT) \
	tests/libmemcached-1.0/generate.$(OBJEXT) \
	tests/libmemcached-1.0/print.$(OBJEXT)
tests_atomsmasher_OBJECTS = $(am_tests_atomsmasher_OBJECTS)
tests_atomsmasher_DEPENDENCIES = $(TESTS_LDADDS)
am__tests_cycle_SOURCES_DIST = tests/cycle.cc
am_tests_cycle_OBJECTS =  \
	tests/tests_cycle-cycle.$(OBJEXT)
tests_cycle_OBJECTS = $(am_tests_cycle_OBJECTS)
tests_cycle_DEPENDENCIES = $(TESTS_LDADDS)
tests_cycle_LINK = $(LIBTOOL) $(AM_V_lt) --tag=CXX $(AM_LIBTOOLFLAGS) \
	$(LIBTOOLFLAGS) --mode=link $(CXXLD) $(tests_cycle_CXXFLAGS) \
	$(CXXFLAGS) $(AM_LDFLAGS) $(LDFLAGS) -o $@
am__tests_failure_SOURCES_DIST = tests/failure.cc clients/execute.cc \
	clients/generator.cc \
	tests/libmemcached-1.0/callback_counter.cc \
	tests/libmemcached-1.0/fetch_all_results.cc \
	tests/libmemcached-1.0/generate.cc \
	tests/libmemcached-1.0/print.cc
am_tests_failure_OBJECTS =  \
	tests/tests_failure-failure.$(OBJEXT) \
	clients/tests_failure-execute.$(OBJEXT) \
	clients/tests_failure-generator.$(OBJEXT) \
	tests/libmemcached-1.0/tests_failure-callback_counter.$(OBJEXT) \
	tests/libmemcached-1.0/tests_failure-fetch_all_results.$(OBJEXT) \
	tests/libmemcached-1.0/tests_failure-generate.$(OBJEXT) \
	tests/libmemcached-1.0/tests_failure-print.$(OBJEXT)
tests_failure_OBJECTS = $(am_tests_failure_OBJECTS)
tests_failure_DEPENDENCIES = $(TESTS_LDADDS)
tests_failure_LINK = $(LIBTOOL) $(AM_V_lt) --tag=CXX \
	$(AM_LIBTOOLFLAGS) $(LIBTOOLFLAGS) --mode=link $(CXXLD) \
	$(tests_failure_CXXFLAGS) $(CXXFLAGS) $(AM_LDFLAGS) $(LDFLAGS) \
	-o $@
am__tests_hash_plus_SOURCES_DIST = tests/hash_plus.cc
am_tests_hash_plus_OBJECTS =  \
	tests/tests_hash_plus-hash_plus.$(OBJEXT)
tests_hash_plus_OBJECTS = $(am_tests_hash_plus_OBJECTS)
tests_hash_plus_DEPENDENCIES =  \
	$(tests_testhashkit_LDADD)
tests_hash_plus_LINK = $(LIBTOOL) $(AM_V_lt) --tag=CXX \
	$(AM_LIBTOOLFLAGS) $(LIBTOOLFLAGS) --mode=link $(CXXLD) \
	$(tests_hash_plus_CXXFLAGS) $(CXXFLAGS) $(AM_LDFLAGS) \
	$(LDFLAGS) -o $@
am__tests_libmemcached_1_0_internals_SOURCES_DIST =  \
	tests/libmemcached-1.0/internals.cc \
	tests/libmemcached-1.0/string.cc
am_tests_libmemcached_1_0_internals_OBJECTS = tests/libmemcached-1.0/tests_libmemcached_1_0_internals-internals.$(OBJEXT) \
	tests/libmemcached-1.0/tests_libmemcached_1_0_internals-string.$(OBJEXT)
tests_libmemcached_1_0_internals_OBJECTS =  \
	$(am_tests_libmemcached_1_0_internals_OBJECTS)
tests_libmemcached_1_0_internals_DEPENDENCIES = libmemcachedinternal/libmemcachedinternal.la \
	libmemcachedinternal/libmemcachedutilinternal.la \
	libtest/libtest.la
tests_libmemcached_1_0_internals_LINK = $(LIBTOOL) $(AM_V_lt) \
	--tag=CXX $(AM_LIBTOOLFLAGS) $(LIBTOOLFLAGS) --mode=link \
	$(CXXLD) $(tests_libmemcached_1_0_internals_CXXFLAGS) \
	$(CXXFLAGS) $(AM_LDFLAGS) $(LDFLAGS) -o $@
am__tests_libmemcached_1_0_sasl_SOURCES_DIST =  \
	tests/libmemcached-1.0/basic.cc \
	tests/libmemcached-1.0/debug.cc \
	tests/libmemcached-1.0/deprecated.cc \
	tests/libmemcached-1.0/error_conditions.cc \
	tests/libmemcached-1.0/ketama.cc \
	tests/libmemcached-1.0/namespace.cc \
	tests/libmemcached-1.0/parser.cc \
	tests/libmemcached-1.0/pool.cc tests/libmemcached-1.0/print.cc \
	tests/libmemcached-1.0/replication.cc \
	tests/libmemcached-1.0/sasl.cc \
	tests/libmemcached-1.0/virtual_buckets.cc clients/execute.cc \
	clients/generator.cc \
	tests/libmemcached-1.0/callback_counter.cc \
	tests/libmemcached-1.0/fetch_all_results.cc \
	tests/libmemcached-1.0/generate.cc
am_tests_libmemcached_1_0_sasl_OBJECTS = tests/libmemcached-1.0/tests_libmemcached_1_0_sasl-basic.$(OBJEXT) \
	tests/libmemcached-1.0/tests_libmemcached_1_0_sasl-debug.$(OBJEXT) \
	tests/libmemcached-1.0/tests_libmemcached_1_0_sasl-deprecated.$(OBJEXT) \
	tests/libmemcached-1.0/tests_libmemcached_1_0_sasl-error_conditions.$(OBJEXT) \
	tests/libmemcached-1.0/tests_libmemcached_1_0_sasl-ketama.$(OBJEXT) \
	tests/libmemcached-1.0/tests_libmemcached_1_0_sasl-namespace.$(OBJEXT) \
	tests/libmemcached-1.0/tests_libmemcached_1_0_sasl-parser.$(OBJEXT) \
	tests/libmemcached-1.0/tests_libmemcached_1_0_sasl-pool.$(OBJEXT) \
	tests/libmemcached-1.0/tests_libmemcached_1_0_sasl-print.$(OBJEXT) \
	tests/libmemcached-1.0/tests_libmemcached_1_0_sasl-replication.$(OBJEXT) \
	tests/libmemcached-1.0/tests_libmemcached_1_0_sasl-sasl.$(OBJEXT) \
	tests/libmemcached-1.0/tests_libmemcached_1_0_sasl-virtual_buckets.$(OBJEXT) \
	clients/tests_libmemcached_1_0_sasl-execute.$(OBJEXT) \
	clients/tests_libmemcached_1_0_sasl-generator.$(OBJEXT) \
	tests/libmemcached-1.0/tests_libmemcached_1_0_sasl-callback_counter.$(OBJEXT) \
	tests/libmemcached-1.0/tests_libmemcached_1_0_sasl-fetch_all_results.$(OBJEXT) \
	tests/libmemcached-1.0/tests_libmemcached_1_0_sasl-generate.$(OBJEXT)
tests_libmemcached_1_0_sasl_OBJECTS =  \
	$(am_tests_libmemcached_1_0_sasl_OBJECTS)
tests_libmemcached_1_0_sasl_DEPENDENCIES =  \
	libmemcached/libmemcached.la \
	libmemcached/libmemcachedutil.la \
	libtest/libtest.la libhashkit/libhashkit.la
tests_libmemcached_1_0_sasl_LINK = $(LIBTOOL) $(AM_V_lt) --tag=CXX \
	$(AM_LIBTOOLFLAGS) $(LIBTOOLFLAGS) --mode=link $(CXXLD) \
	$(tests_libmemcached_1_0_sasl_CXXFLAGS) $(CXXFLAGS) \
	$(AM_LDFLAGS) $(LDFLAGS) -o $@
am__tests_libmemcached_1_0_testapp_SOURCES_DIST =  \
	clients/generator.cc clients/execute.cc \
	tests/libmemcached-1.0/all_tests.cc \
	tests/libmemcached-1.0/basic.cc \
	tests/libmemcached-1.0/callback_counter.cc \
	tests/libmemcached-1.0/callbacks.cc \
	tests/libmemcached-1.0/debug.cc \
	tests/libmemcached-1.0/deprecated.cc \
	tests/libmemcached-1.0/dump.cc \
	tests/libmemcached-1.0/encoding_key.cc \
	tests/libmemcached-1.0/error_conditions.cc \
	tests/libmemcached-1.0/exist.cc \
	tests/libmemcached-1.0/fetch_all_results.cc \
	tests/libmemcached-1.0/generate.cc \
	tests/libmemcached-1.0/haldenbrand.cc \
	tests/libmemcached-1.0/ketama.cc \
	tests/libmemcached-1.0/mem_functions.cc \
	tests/libmemcached-1.0/memcached_get.cc \
	tests/libmemcached-1.0/namespace.cc \
	tests/libmemcached-1.0/parser.cc \
	tests/libmemcached-1.0/pool.cc tests/libmemcached-1.0/print.cc \
	tests/libmemcached-1.0/replication.cc \
	tests/libmemcached-1.0/server_add.cc \
	tests/libmemcached-1.0/setup_and_teardowns.cc \
	tests/libmemcached-1.0/stat.cc tests/libmemcached-1.0/touch.cc \
	tests/libmemcached-1.0/virtual_buckets.cc
am_tests_libmemcached_1_0_testapp_OBJECTS = clients/tests_libmemcached_1_0_testapp-generator.$(OBJEXT) \
	clients/tests_libmemcached_1_0_testapp-execute.$(OBJEXT) \
	tests/libmemcached-1.0/tests_libmemcached_1_0_testapp-all_tests.$(OBJEXT) \
	tests/libmemcached-1.0/tests_libmemcached_1_0_testapp-basic.$(OBJEXT) \
	tests/libmemcached-1.0/tests_libmemcached_1_0_testapp-callback_counter.$(OBJEXT) \
	tests/libmemcached-1.0/tests_libmemcached_1_0_testapp-callbacks.$(OBJEXT) \
	tests/libmemcached-1.0/tests_libmemcached_1_0_testapp-debug.$(OBJEXT) \
	tests/libmemcached-1.0/tests_libmemcached_1_0_testapp-deprecated.$(OBJEXT) \
	tests/libmemcached-1.0/tests_libmemcached_1_0_testapp-dump.$(OBJEXT) \
	tests/libmemcached-1.0/tests_libmemcached_1_0_testapp-encoding_key.$(OBJEXT) \
	tests/libmemcached-1.0/tests_libmemcached_1_0_testapp-error_conditions.$(OBJEXT) \
	tests/libmemcached-1.0/tests_libmemcached_1_0_testapp-exist.$(OBJEXT) \
	tests/libmemcached-1.0/tests_libmemcached_1_0_testapp-fetch_all_results.$(OBJEXT) \
	tests/libmemcached-1.0/tests_libmemcached_1_0_testapp-generate.$(OBJEXT) \
	tests/libmemcached-1.0/tests_libmemcached_1_0_testapp-haldenbrand.$(OBJEXT) \
	tests/libmemcached-1.0/tests_libmemcached_1_0_testapp-ketama.$(OBJEXT) \
	tests/libmemcached-1.0/tests_libmemcached_1_0_testapp-mem_functions.$(OBJEXT) \
	tests/libmemcached-1.0/tests_libmemcached_1_0_testapp-memcached_get.$(OBJEXT) \
	tests/libmemcached-1.0/tests_libmemcached_1_0_testapp-namespace.$(OBJEXT) \
	tests/libmemcached-1.0/tests_libmemcached_1_0_testapp-parser.$(OBJEXT) \
	tests/libmemcached-1.0/tests_libmemcached_1_0_testapp-pool.$(OBJEXT) \
	tests/libmemcached-1.0/tests_libmemcached_1_0_testapp-print.$(OBJEXT) \
	tests/libmemcached-1.0/tests_libmemcached_1_0_testapp-replication.$(OBJEXT) \
	tests/libmemcached-1.0/tests_libmemcached_1_0_testapp-server_add.$(OBJEXT) \
	tests/libmemcached-1.0/tests_libmemcached_1_0_testapp-setup_and_teardowns.$(OBJEXT) \
	tests/libmemcached-1.0/tests_libmemcached_1_0_testapp-stat.$(OBJEXT) \
	tests/libmemcached-1.0/tests_libmemcached_1_0_testapp-touch.$(OBJEXT) \
	tests/libmemcached-1.0/tests_libmemcached_1_0_testapp-virtual_buckets.$(OBJEXT)
tests_libmemcached_1_0_testapp_OBJECTS =  \
	$(am_tests_libmemcached_1_0_testapp_OBJECTS)
tests_libmemcached_1_0_testapp_DEPENDENCIES =  \
	libmemcached/libmemcached.la \
	libmemcached/libmemcachedutil.la \
	libtest/libtest.la libhashkit/libhashkit.la
tests_libmemcached_1_0_testapp_LINK = $(LIBTOOL) $(AM_V_lt) --tag=CXX \
	$(AM_LIBTOOLFLAGS) $(LIBTOOLFLAGS) --mode=link $(CXXLD) \
	$(tests_libmemcached_1_0_testapp_CXXFLAGS) $(CXXFLAGS) \
	$(AM_LDFLAGS) $(LDFLAGS) -o $@
am__tests_libmemcached_1_0_testsocket_SOURCES_DIST =  \
	clients/execute.cc clients/generator.cc \
	tests/libmemcached-1.0/all_tests_socket.cc \
	tests/libmemcached-1.0/basic.cc \
	tests/libmemcached-1.0/callback_counter.cc \
	tests/libmemcached-1.0/callbacks.cc \
	tests/libmemcached-1.0/debug.cc \
	tests/libmemcached-1.0/deprecated.cc \
	tests/libmemcached-1.0/dump.cc \
	tests/libmemcached-1.0/encoding_key.cc \
	tests/libmemcached-1.0/error_conditions.cc \
	tests/libmemcached-1.0/exist.cc \
	tests/libmemcached-1.0/fetch_all_results.cc \
	tests/libmemcached-1.0/generate.cc \
	tests/libmemcached-1.0/haldenbrand.cc \
	tests/libmemcached-1.0/ketama.cc \
	tests/libmemcached-1.0/mem_functions.cc \
	tests/libmemcached-1.0/memcached_get.cc \
	tests/libmemcached-1.0/namespace.cc \
	tests/libmemcached-1.0/parser.cc \
	tests/libmemcached-1.0/pool.cc tests/libmemcached-1.0/print.cc \
	tests/libmemcached-1.0/replication.cc \
	tests/libmemcached-1.0/server_add.cc \
	tests/libmemcached-1.0/setup_and_teardowns.cc \
	tests/libmemcached-1.0/stat.cc tests/libmemcached-1.0/touch.cc \
	tests/libmemcached-1.0/virtual_buckets.cc
am_tests_libmemcached_1_0_testsocket_OBJECTS = clients/tests_libmemcached_1_0_testsocket-execute.$(OBJEXT) \
	clients/tests_libmemcached_1_0_testsocket-generator.$(OBJEXT) \
	tests/libmemcached-1.0/tests_libmemcached_1_0_testsocket-all_tests_socket.$(OBJEXT) \
	tests/libmemcached-1.0/tests_libmemcached_1_0_testsocket-basic.$(OBJEXT) \
	tests/libmemcached-1.0/tests_libmemcached_1_0_testsocket-callback_counter.$(OBJEXT) \
	tests/libmemcached-1.0/tests_libmemcached_1_0_testsocket-callbacks.$(OBJEXT) \
	tests/libmemcached-1.0/tests_libmemcached_1_0_testsocket-debug.$(OBJEXT) \
	tests/libmemcached-1.0/tests_libmemcached_1_0_testsocket-deprecated.$(OBJEXT) \
	tests/libmemcached-1.0/tests_libmemcached_1_0_testsocket-dump.$(OBJEXT) \
	tests/libmemcached-1.0/tests_libmemcached_1_0_testsocket-encoding_key.$(OBJEXT) \
	tests/libmemcached-1.0/tests_libmemcached_1_0_testsocket-error_conditions.$(OBJEXT) \
	tests/libmemcached-1.0/tests_libmemcached_1_0_testsocket-exist.$(OBJEXT) \
	tests/libmemcached-1.0/tests_libmemcached_1_0_testsocket-fetch_all_results.$(OBJEXT) \
	tests/libmemcached-1.0/tests_libmemcached_1_0_testsocket-generate.$(OBJEXT) \
	tests/libmemcached-1.0/tests_libmemcached_1_0_testsocket-haldenbrand.$(OBJEXT) \
	tests/libmemcached-1.0/tests_libmemcached_1_0_testsocket-ketama.$(OBJEXT) \
	tests/libmemcached-1.0/tests_libmemcached_1_0_testsocket-mem_functions.$(OBJEXT) \
	tests/libmemcached-1.0/tests_libmemcached_1_0_testsocket-memcached_get.$(OBJEXT) \
	tests/libmemcached-1.0/tests_libmemcached_1_0_testsocket-namespace.$(OBJEXT) \
	tests/libmemcached-1.0/tests_libmemcached_1_0_testsocket-parser.$(OBJEXT) \
	tests/libmemcached-1.0/tests_libmemcached_1_0_testsocket-pool.$(OBJEXT) \
	tests/libmemcached-1.0/tests_libmemcached_1_0_testsocket-print.$(OBJEXT) \
	tests/libmemcached-1.0/tests_libmemcached_1_0_testsocket-replication.$(OBJEXT) \
	tests/libmemcached-1.0/tests_libmemcached_1_0_testsocket-server_add.$(OBJEXT) \
	tests/libmemcached-1.0/tests_libmemcached_1_0_testsocket-setup_and_teardowns.$(OBJEXT) \
	tests/libmemcached-1.0/tests_libmemcached_1_0_testsocket-stat.$(OBJEXT) \
	tests/libmemcached-1.0/tests_libmemcached_1_0_testsocket-touch.$(OBJEXT) \
	tests/libmemcached-1.0/tests_libmemcached_1_0_testsocket-virtual_buckets.$(OBJEXT)
tests_libmemcached_1_0_testsocket_OBJECTS =  \
	$(am_tests_libmemcached_1_0_testsocket_OBJECTS)
tests_libmemcached_1_0_testsocket_DEPENDENCIES =  \
	libmemcached/libmemcached.la \
	libmemcached/libmemcachedutil.la \
	libtest/libtest.la libhashkit/libhashkit.la
tests_libmemcached_1_0_testsocket_LINK = $(LIBTOOL) $(AM_V_lt) \
	--tag=CXX $(AM_LIBTOOLFLAGS) $(LIBTOOLFLAGS) --mode=link \
	$(CXXLD) $(tests_libmemcached_1_0_testsocket_CXXFLAGS) \
	$(CXXFLAGS) $(AM_LDFLAGS) $(LDFLAGS) -o $@
am__tests_memcapable_SOURCES_DIST = tests/memcapable.cc
am_tests_memcapable_OBJECTS = tests/tests_memcapable-memcapable.$(OBJEXT)
tests_memcapable_OBJECTS = $(am_tests_memcapable_OBJECTS)
tests_memcapable_DEPENDENCIES = libtest/libtest.la \
	$(TESTS_LDADDS)
tests_memcapable_LINK = $(LIBTOOL) $(AM_V_lt) --tag=CXX \
	$(AM_LIBTOOLFLAGS) $(LIBTOOLFLAGS) --mode=link $(CXXLD) \
	$(tests_memcapable_CXXFLAGS) $(CXXFLAGS) $(AM_LDFLAGS) \
	$(LDFLAGS) -o $@
am__tests_memcat_SOURCES_DIST = tests/memcat.cc
am_tests_memcat_OBJECTS =  \
	tests/tests_memcat-memcat.$(OBJEXT)
tests_memcat_OBJECTS = $(am_tests_memcat_OBJECTS)
tests_memcat_DEPENDENCIES = libtest/libtest.la \
	$(TESTS_LDADDS)
tests_memcat_LINK = $(LIBTOOL) $(AM_V_lt) --tag=CXX $(AM_LIBTOOLFLAGS) \
	$(LIBTOOLFLAGS) --mode=link $(CXXLD) $(tests_memcat_CXXFLAGS) \
	$(CXXFLAGS) $(AM_LDFLAGS) $(LDFLAGS) -o $@
am__tests_memcp_SOURCES_DIST = tests/memcp.cc
am_tests_memcp_OBJECTS =  \
	tests/tests_memcp-memcp.$(OBJEXT)
tests_memcp_OBJECTS = $(am_tests_memcp_OBJECTS)
tests_memcp_DEPENDENCIES = libtest/libtest.la \
	$(TESTS_LDADDS)
tests_memcp_LINK = $(LIBTOOL) $(AM_V_lt) --tag=CXX $(AM_LIBTOOLFLAGS) \
	$(LIBTOOLFLAGS) --mode=link $(CXXLD) $(tests_memcp_CXXFLAGS) \
	$(CXXFLAGS) $(AM_LDFLAGS) $(LDFLAGS) -o $@
am__tests_memdump_SOURCES_DIST = tests/memdump.cc
am_tests_memdump_OBJECTS =  \
	tests/tests_memdump-memdump.$(OBJEXT)
tests_memdump_OBJECTS = $(am_tests_memdump_OBJECTS)
tests_memdump_DEPENDENCIES = libtest/libtest.la \
	$(TESTS_LDADDS)
tests_memdump_LINK = $(LIBTOOL) $(AM_V_lt) --tag=CXX \
	$(AM_LIBTOOLFLAGS) $(LIBTOOLFLAGS) --mode=link $(CXXLD) \
	$(tests_memdump_CXXFLAGS) $(CXXFLAGS) $(AM_LDFLAGS) $(LDFLAGS) \
	-o $@
am__tests_memerror_SOURCES_DIST = tests/memerror.cc
am_tests_memerror_OBJECTS =  \
	tests/tests_memerror-memerror.$(OBJEXT)
tests_memerror_OBJECTS = $(am_tests_memerror_OBJECTS)
tests_memerror_DEPENDENCIES = libtest/libtest.la \
	$(TESTS_LDADDS)
tests_memerror_LINK = $(LIBTOOL) $(AM_V_lt) --tag=CXX \
	$(AM_LIBTOOLFLAGS) $(LIBTOOLFLAGS) --mode=link $(CXXLD) \
	$(tests_memerror_CXXFLAGS) $(CXXFLAGS) $(AM_LDFLAGS) \
	$(LDFLAGS) -o $@
am__tests_memexist_SOURCES_DIST = tests/memexist.cc
am_tests_memexist_OBJECTS =  \
	tests/tests_memexist-memexist.$(OBJEXT)
tests_memexist_OBJECTS = $(am_tests_memexist_OBJECTS)
tests_memexist_DEPENDENCIES = libtest/libtest.la \
	$(TESTS_LDADDS)
tests_memexist_LINK = $(LIBTOOL) $(AM_V_lt) --tag=CXX \
	$(AM_LIBTOOLFLAGS) $(LIBTOOLFLAGS) --mode=link $(CXXLD) \
	$(tests_memexist_CXXFLAGS) $(CXXFLAGS) $(AM_LDFLAGS) \
	$(LDFLAGS) -o $@
am__tests_memflush_SOURCES_DIST = tests/memflush.cc
am_tests_memflush_OBJECTS =  \
	tests/tests_memflush-memflush.$(OBJEXT)
tests_memflush_OBJECTS = $(am_tests_memflush_OBJECTS)
tests_memflush_DEPENDENCIES = libtest/libtest.la \
	$(TESTS_LDADDS)
tests_memflush_LINK = $(LIBTOOL) $(AM_V_lt) --tag=CXX \
	$(AM_LIBTOOLFLAGS) $(LIBTOOLFLAGS) --mode=link $(CXXLD) \
	$(tests_memflush_CXXFLAGS) $(CXXFLAGS) $(AM_LDFLAGS) \
	$(LDFLAGS) -o $@
am__tests_memping_SOURCES_DIST = tests/memping.cc
am_tests_memping_OBJECTS =  \
	tests/tests_memping-memping.$(OBJEXT)
tests_memping_OBJECTS = $(am_tests_memping_OBJECTS)
tests_memping_DEPENDENCIES = libtest/libtest.la \
	$(TESTS_LDADDS)
tests_memping_LINK = $(LIBTOOL) $(AM_V_lt) --tag=CXX \
	$(AM_LIBTOOLFLAGS) $(LIBTOOLFLAGS) --mode=link $(CXXLD) \
	$(tests_memping_CXXFLAGS) $(CXXFLAGS) $(AM_LDFLAGS) $(LDFLAGS) \
	-o $@
am__tests_memrm_SOURCES_DIST = tests/memrm.cc
am_tests_memrm_OBJECTS =  \
	tests/tests_memrm-memrm.$(OBJEXT)
tests_memrm_OBJECTS = $(am_tests_memrm_OBJECTS)
tests_memrm_DEPENDENCIES = libtest/libtest.la \
	$(TESTS_LDADDS)
tests_memrm_LINK = $(LIBTOOL) $(AM_V_lt) --tag=CXX $(AM_LIBTOOLFLAGS) \
	$(LIBTOOLFLAGS) --mode=link $(CXXLD) $(tests_memrm_CXXFLAGS) \
	$(CXXFLAGS) $(AM_LDFLAGS) $(LDFLAGS) -o $@
am__tests_memslap_SOURCES_DIST = tests/memslap.cc
am_tests_memslap_OBJECTS =  \
	tests/tests_memslap-memslap.$(OBJEXT)
tests_memslap_OBJECTS = $(am_tests_memslap_OBJECTS)
tests_memslap_DEPENDENCIES = libtest/libtest.la \
	$(TESTS_LDADDS)
tests_memslap_LINK = $(LIBTOOL) $(AM_V_lt) --tag=CXX \
	$(AM_LIBTOOLFLAGS) $(LIBTOOLFLAGS) --mode=link $(CXXLD) \
	$(tests_memslap_CXXFLAGS) $(CXXFLAGS) $(AM_LDFLAGS) $(LDFLAGS) \
	-o $@
am__tests_memstat_SOURCES_DIST = tests/memstat.cc
am_tests_memstat_OBJECTS =  \
	tests/tests_memstat-memstat.$(OBJEXT)
tests_memstat_OBJECTS = $(am_tests_memstat_OBJECTS)
tests_memstat_DEPENDENCIES = libtest/libtest.la \
	$(TESTS_LDADDS)
tests_memstat_LINK = $(LIBTOOL) $(AM_V_lt) --tag=CXX \
	$(AM_LIBTOOLFLAGS) $(LIBTOOLFLAGS) --mode=link $(CXXLD) \
	$(tests_memstat_CXXFLAGS) $(CXXFLAGS) $(AM_LDFLAGS) $(LDFLAGS) \
	-o $@
am__tests_memtouch_SOURCES_DIST = tests/memtouch.cc
am_tests_memtouch_OBJECTS =  \
	tests/tests_memtouch-memtouch.$(OBJEXT)
tests_memtouch_OBJECTS = $(am_tests_memtouch_OBJECTS)
tests_memtouch_DEPENDENCIES = libtest/libtest.la \
	$(TESTS_LDADDS)
tests_memtouch_LINK = $(LIBTOOL) $(AM_V_lt) --tag=CXX \
	$(AM_LIBTOOLFLAGS) $(LIBTOOLFLAGS) --mode=link $(CXXLD) \
	$(tests_memtouch_CXXFLAGS) $(CXXFLAGS) $(AM_LDFLAGS) \
	$(LDFLAGS) -o $@
am__tests_parser_SOURCES_DIST = tests/parser.cc
am_tests_parser_OBJECTS =  \
	tests/tests_parser-parser.$(OBJEXT)
tests_parser_OBJECTS = $(am_tests_parser_OBJECTS)
tests_parser_DEPENDENCIES = $(TESTS_LDADDS)
tests_parser_LINK = $(LIBTOOL) $(AM_V_lt) --tag=CXX $(AM_LIBTOOLFLAGS) \
	$(LIBTOOLFLAGS) --mode=link $(CXXLD) $(tests_parser_CXXFLAGS) \
	$(CXXFLAGS) $(AM_LDFLAGS) $(LDFLAGS) -o $@
am__tests_testhashkit_SOURCES_DIST = tests/hashkit_functions.cc
am_tests_testhashkit_OBJECTS =  \
	tests/hashkit_functions.$(OBJEXT)
tests_testhashkit_OBJECTS = $(am_tests_testhashkit_OBJECTS)
tests_testhashkit_DEPENDENCIES =  \
	libtest/libtest.la libhashkit/libhashkit.la \
	$(TESTS_LDADDS)
am__tests_testplus_SOURCES_DIST = clients/execute.cc \
	clients/generator.cc \
	tests/libmemcached-1.0/callback_counter.cc \
	tests/libmemcached-1.0/fetch_all_results.cc \
	tests/libmemcached-1.0/generate.cc \
	tests/libmemcached-1.0/plus.cpp \
	tests/libmemcached-1.0/print.cc
am_tests_testplus_OBJECTS =  \
	clients/tests_testplus-execute.$(OBJEXT) \
	clients/tests_testplus-generator.$(OBJEXT) \
	tests/libmemcached-1.0/tests_testplus-callback_counter.$(OBJEXT) \
	tests/libmemcached-1.0/tests_testplus-fetch_all_results.$(OBJEXT) \
	tests/libmemcached-1.0/tests_testplus-generate.$(OBJEXT) \
	tests/libmemcached-1.0/tests_testplus-plus.$(OBJEXT) \
	tests/libmemcached-1.0/tests_testplus-print.$(OBJEXT)
tests_testplus_OBJECTS = $(am_tests_testplus_OBJECTS)
tests_testplus_DEPENDENCIES = $(TESTS_LDADDS)
tests_testplus_LINK = $(LIBTOOL) $(AM_V_lt) --tag=CXX \
	$(AM_LIBTOOLFLAGS) $(LIBTOOLFLAGS) --mode=link $(CXXLD) \
	$(tests_testplus_CXXFLAGS) $(CXXFLAGS) $(AM_LDFLAGS) \
	$(LDFLAGS) -o $@
am__tests_testudp_SOURCES_DIST = clients/execute.cc \
	clients/generator.cc \
	tests/libmemcached-1.0/callback_counter.cc \
	tests/libmemcached-1.0/fetch_all_results.cc \
	tests/libmemcached-1.0/generate.cc \
	tests/libmemcached-1.0/print.cc tests/mem_udp.cc
am_tests_testudp_OBJECTS =  \
	clients/execute.$(OBJEXT) \
	clients/generator.$(OBJEXT) \
	tests/libmemcached-1.0/callback_counter.$(OBJEXT) \
	tests/libmemcached-1.0/fetch_all_results.$(OBJEXT) \
	tests/libmemcached-1.0/generate.$(OBJEXT) \
	tests/libmemcached-1.0/print.$(OBJEXT) \
	tests/mem_udp.$(OBJEXT)
tests_testudp_OBJECTS = $(am_tests_testudp_OBJECTS)
tests_testudp_DEPENDENCIES = $(TESTS_LDADDS)
AM_V_P = $(am__v_P_$(V))
am__v_P_ = $(am__v_P_$(AM_DEFAULT_VERBOSITY))
am__v_P_0 = false
am__v_P_1 = :
AM_V_GEN = $(am__v_GEN_$(V))
am__v_GEN_ = $(am__v_GEN_$(AM_DEFAULT_VERBOSITY))
am__v_GEN_0 = @echo "  GEN     " $@;
am__v_GEN_1 =
AM_V_at = $(am__v_at_$(V))
am__v_at_ = $(am__v_at_$(AM_DEFAULT_VERBOSITY))
am__v_at_0 = @
am__v_at_1 =
DEFAULT_INCLUDES = -I.
depcomp = $(SHELL) $(top_srcdir)/build-aux/depcomp
am__depfiles_maybe = depfiles
am__mv = mv -f
COMPILE = $(CC) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) \
	$(CPPFLAGS) $(AM_CFLAGS) $(CFLAGS)
LTCOMPILE = $(LIBTOOL) $(AM_V_lt) --tag=CC $(AM_LIBTOOLFLAGS) \
	$(LIBTOOLFLAGS) --mode=compile $(CC) $(DEFS) \
	$(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(CPPFLAGS) \
	$(AM_CFLAGS) $(CFLAGS)
AM_V_CC = $(am__v_CC_$(V))
am__v_CC_ = $(am__v_CC_$(AM_DEFAULT_VERBOSITY))
am__v_CC_0 = @echo "  CC      " $@;
am__v_CC_1 =
CCLD = $(CC)
LINK = $(LIBTOOL) $(AM_V_lt) --tag=CC $(AM_LIBTOOLFLAGS) \
	$(LIBTOOLFLAGS) --mode=link $(CCLD) $(AM_CFLAGS) $(CFLAGS) \
	$(AM_LDFLAGS) $(LDFLAGS) -o $@
AM_V_CCLD = $(am__v_CCLD_$(V))
am__v_CCLD_ = $(am__v_CCLD_$(AM_DEFAULT_VERBOSITY))
am__v_CCLD_0 = @echo "  CCLD    " $@;
am__v_CCLD_1 =
CXXCOMPILE = $(CXX) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) \
	$(AM_CPPFLAGS) $(CPPFLAGS) $(AM_CXXFLAGS) $(CXXFLAGS)
LTCXXCOMPILE = $(LIBTOOL) $(AM_V_lt) --tag=CXX $(AM_LIBTOOLFLAGS) \
	$(LIBTOOLFLAGS) --mode=compile $(CXX) $(DEFS) \
	$(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(CPPFLAGS) \
	$(AM_CXXFLAGS) $(CXXFLAGS)
AM_V_CXX = $(am__v_CXX_$(V))
am__v_CXX_ = $(am__v_CXX_$(AM_DEFAULT_VERBOSITY))
am__v_CXX_0 = @echo "  CXX     " $@;
am__v_CXX_1 =
CXXLD = $(CXX)
CXXLINK = $(LIBTOOL) $(AM_V_lt) --tag=CXX $(AM_LIBTOOLFLAGS) \
	$(LIBTOOLFLAGS) --mode=link $(CXXLD) $(AM_CXXFLAGS) \
	$(CXXFLAGS) $(AM_LDFLAGS) $(LDFLAGS) -o $@
AM_V_CXXLD = $(am__v_CXXLD_$(V))
am__v_CXXLD_ = $(am__v_CXXLD_$(AM_DEFAULT_VERBOSITY))
am__v_CXXLD_0 = @echo "  CXXLD   " $@;
am__v_CXXLD_1 =
SOURCES = $(clients_libutilities_la_SOURCES) \
	$(libhashkit_libhashkit_la_SOURCES) \
	$(libhashkit_libhashkitinc_la_SOURCES) \
	$(libmemcached_libmemcached_la_SOURCES) \
	$(libmemcached_libmemcachedprotocol_la_SOURCES) \
	$(libmemcached_libmemcachedutil_la_SOURCES) \
	$(libmemcachedinternal_libmemcachedinternal_la_SOURCES) \
	$(libmemcachedinternal_libmemcachedutilinternal_la_SOURCES) \
	$(libtest_libtest_la_SOURCES) $(clients_memaslap_SOURCES) \
	$(clients_memcapable_SOURCES) $(clients_memcat_SOURCES) \
	$(clients_memcp_SOURCES) $(clients_memdump_SOURCES) \
	$(clients_memerror_SOURCES) $(clients_memexist_SOURCES) \
	$(clients_memflush_SOURCES) $(clients_memparse_SOURCES) \
	$(clients_memping_SOURCES) $(clients_memrm_SOURCES) \
	$(clients_memslap_SOURCES) $(clients_memstat_SOURCES) \
	$(clients_memtouch_SOURCES) $(example_memcached_light_SOURCES) \
	$(libmemcached_1_0_t_c_sasl_test_SOURCES) \
	$(libmemcached_1_0_t_c_test_SOURCES) \
	$(libmemcached_1_0_t_cc_test_SOURCES) $(libtest_abort_SOURCES) \
	$(libtest_backtrace_SOURCES) $(libtest_core_count_SOURCES) \
	$(libtest_skiptest_SOURCES) $(libtest_unittest_SOURCES) \
	$(libtest_wait_SOURCES) $(tests_atomsmasher_SOURCES) \
	$(tests_cycle_SOURCES) $(tests_failure_SOURCES) \
	$(tests_hash_plus_SOURCES) \
	$(tests_libmemcached_1_0_internals_SOURCES) \
	$(tests_libmemcached_1_0_sasl_SOURCES) \
	$(tests_libmemcached_1_0_testapp_SOURCES) \
	$(tests_libmemcached_1_0_testsocket_SOURCES) \
	$(tests_memcapable_SOURCES) $(tests_memcat_SOURCES) \
	$(tests_memcp_SOURCES) $(tests_memdump_SOURCES) \
	$(tests_memerror_SOURCES) $(tests_memexist_SOURCES) \
	$(tests_memflush_SOURCES) $(tests_memping_SOURCES) \
	$(tests_memrm_SOURCES) $(tests_memslap_SOURCES) \
	$(tests_memstat_SOURCES) $(tests_memtouch_SOURCES) \
	$(tests_parser_SOURCES) $(tests_testhashkit_SOURCES) \
	$(tests_testplus_SOURCES) $(tests_testudp_SOURCES)
DIST_SOURCES = $(am__clients_libutilities_la_SOURCES_DIST) \
	$(am__libhashkit_libhashkit_la_SOURCES_DIST) \
	$(am__libhashkit_libhashkitinc_la_SOURCES_DIST) \
	$(am__libmemcached_libmemcached_la_SOURCES_DIST) \
	$(am__libmemcached_libmemcachedprotocol_la_SOURCES_DIST) \
	$(am__libmemcached_libmemcachedutil_la_SOURCES_DIST) \
	$(am__libmemcachedinternal_libmemcachedinternal_la_SOURCES_DIST) \
	$(am__libmemcachedinternal_libmemcachedutilinternal_la_SOURCES_DIST) \
	$(am__libtest_libtest_la_SOURCES_DIST) \
	$(am__clients_memaslap_SOURCES_DIST) \
	$(am__clients_memcapable_SOURCES_DIST) \
	$(am__clients_memcat_SOURCES_DIST) \
	$(am__clients_memcp_SOURCES_DIST) \
	$(am__clients_memdump_SOURCES_DIST) \
	$(am__clients_memerror_SOURCES_DIST) \
	$(am__clients_memexist_SOURCES_DIST) \
	$(am__clients_memflush_SOURCES_DIST) \
	$(am__clients_memparse_SOURCES_DIST) \
	$(am__clients_memping_SOURCES_DIST) \
	$(am__clients_memrm_SOURCES_DIST) \
	$(am__clients_memslap_SOURCES_DIST) \
	$(am__clients_memstat_SOURCES_DIST) \
	$(am__clients_memtouch_SOURCES_DIST) \
	$(am__example_memcached_light_SOURCES_DIST) \
	$(am__libmemcached_1_0_t_c_sasl_test_SOURCES_DIST) \
	$(am__libmemcached_1_0_t_c_test_SOURCES_DIST) \
	$(am__libmemcached_1_0_t_cc_test_SOURCES_DIST) \
	$(am__libtest_abort_SOURCES_DIST) \
	$(am__libtest_backtrace_SOURCES_DIST) \
	$(am__libtest_core_count_SOURCES_DIST) \
	$(am__libtest_skiptest_SOURCES_DIST) \
	$(am__libtest_unittest_SOURCES_DIST) \
	$(am__libtest_wait_SOURCES_DIST) \
	$(am__tests_atomsmasher_SOURCES_DIST) \
	$(am__tests_cycle_SOURCES_DIST) \
	$(am__tests_failure_SOURCES_DIST) \
	$(am__tests_hash_plus_SOURCES_DIST) \
	$(am__tests_libmemcached_1_0_internals_SOURCES_DIST) \
	$(am__tests_libmemcached_1_0_sasl_SOURCES_DIST) \
	$(am__tests_libmemcached_1_0_testapp_SOURCES_DIST) \
	$(am__tests_libmemcached_1_0_testsocket_SOURCES_DIST) \
	$(am__tests_memcapable_SOURCES_DIST) \
	$(am__tests_memcat_SOURCES_DIST) \
	$(am__tests_memcp_SOURCES_DIST) \
	$(am__tests_memdump_SOURCES_DIST) \
	$(am__tests_memerror_SOURCES_DIST) \
	$(am__tests_memexist_SOURCES_DIST) \
	$(am__tests_memflush_SOURCES_DIST) \
	$(am__tests_memping_SOURCES_DIST) \
	$(am__tests_memrm_SOURCES_DIST) \
	$(am__tests_memslap_SOURCES_DIST) \
	$(am__tests_memstat_SOURCES_DIST) \
	$(am__tests_memtouch_SOURCES_DIST) \
	$(am__tests_parser_SOURCES_DIST) \
	$(am__tests_testhashkit_SOURCES_DIST) \
	$(am__tests_testplus_SOURCES_DIST) \
	$(am__tests_testudp_SOURCES_DIST)
am__can_run_installinfo = \
  case $$AM_UPDATE_INFO_DIR in \
    n|no|NO) false;; \
    *) (install-info --version) >/dev/null 2>&1;; \
  esac
man1dir = $(mandir)/man1
man3dir = $(mandir)/man3
NROFF = nroff
MANS = $(dist_man_MANS) $(man_MANS)
am__dist_aclocal_DATA_DIST = m4/ax_libmemcached.m4
DATA = $(dist_aclocal_DATA) $(pkgconfig_DATA)
am__nobase_include_HEADERS_DIST = libhashkit-1.0/algorithm.h \
	libhashkit-1.0/behavior.h libhashkit-1.0/configure.h \
	libhashkit-1.0/digest.h libhashkit-1.0/function.h \
	libhashkit-1.0/has.h libhashkit-1.0/hashkit.h \
	libhashkit-1.0/hashkit.hpp libhashkit-1.0/strerror.h \
	libhashkit-1.0/string.h libhashkit-1.0/str_algorithm.h \
	libhashkit-1.0/types.h libhashkit-1.0/visibility.h \
	libhashkit/hashkit.h libmemcached/memcached.h \
	libmemcached/memcached.hpp libmemcached/util.h \
	libmemcached-1.0/struct/allocator.h \
	libmemcached-1.0/struct/analysis.h \
	libmemcached-1.0/struct/callback.h \
	libmemcached-1.0/struct/memcached.h \
	libmemcached-1.0/struct/result.h \
	libmemcached-1.0/struct/sasl.h \
	libmemcached-1.0/struct/server.h \
	libmemcached-1.0/struct/stat.h \
	libmemcached-1.0/struct/string.h \
	libmemcached-1.0/types/behavior.h \
	libmemcached-1.0/types/callback.h \
	libmemcached-1.0/types/connection.h \
	libmemcached-1.0/types/hash.h libmemcached-1.0/types/return.h \
	libmemcached-1.0/types/server_distribution.h \
	libmemcached-1.0/alloc.h libmemcached-1.0/allocators.h \
	libmemcached-1.0/analyze.h libmemcached-1.0/auto.h \
	libmemcached-1.0/basic_string.h libmemcached-1.0/behavior.h \
	libmemcached-1.0/callback.h libmemcached-1.0/callbacks.h \
	libmemcached-1.0/configure.h libmemcached-1.0/defaults.h \
	libmemcached-1.0/delete.h libmemcached-1.0/deprecated_types.h \
	libmemcached-1.0/dump.h libmemcached-1.0/encoding_key.h \
	libmemcached-1.0/error.h libmemcached-1.0/exception.hpp \
	libmemcached-1.0/exist.h libmemcached-1.0/fetch.h \
	libmemcached-1.0/flush.h libmemcached-1.0/flush_buffers.h \
	libmemcached-1.0/get.h libmemcached-1.0/hash.h \
	libmemcached-1.0/limits.h libmemcached-1.0/memcached.h \
	libmemcached-1.0/memcached.hpp libmemcached-1.0/options.h \
	libmemcached-1.0/parse.h libmemcached-1.0/platform.h \
	libmemcached-1.0/quit.h libmemcached-1.0/result.h \
	libmemcached-1.0/return.h libmemcached-1.0/sasl.h \
	libmemcached-1.0/server.h libmemcached-1.0/server_list.h \
	libmemcached-1.0/stats.h libmemcached-1.0/storage.h \
	libmemcached-1.0/strerror.h libmemcached-1.0/touch.h \
	libmemcached-1.0/triggers.h libmemcached-1.0/types.h \
	libmemcached-1.0/verbosity.h libmemcached-1.0/version.h \
	libmemcached-1.0/visibility.h \
	libmemcachedprotocol-0.0/binary.h \
	libmemcachedprotocol-0.0/callback.h \
	libmemcachedprotocol-0.0/handler.h \
	libmemcachedprotocol-0.0/vbucket.h \
	libmemcachedutil-1.0/flush.h libmemcachedutil-1.0/ostream.hpp \
	libmemcachedutil-1.0/pid.h libmemcachedutil-1.0/ping.h \
	libmemcachedutil-1.0/pool.h libmemcachedutil-1.0/util.h \
	libmemcachedutil-1.0/version.h
am__noinst_HEADERS_DIST = libhashkit/aes.h libhashkit/algorithm.h \
	libhashkit/murmur3.h libhashkit/common.h libhashkit/is.h \
	libhashkit/rijndael.hpp libhashkit/string.h \
	libmemcached/csl/common.h libmemcached/csl/context.h \
	libmemcached/csl/parser.h libmemcached/csl/scanner.h \
	libmemcached/csl/server.h libmemcached/csl/symbol.h \
	libmemcached/array.h libmemcached/assert.hpp \
	libmemcached/backtrace.hpp libmemcached/behavior.hpp \
	libmemcached/byteorder.h libmemcached/common.h \
	libmemcached/connect.hpp libmemcached/continuum.hpp \
	libmemcached/do.hpp libmemcached/encoding_key.h \
	libmemcached/error.hpp libmemcached/flag.hpp \
	libmemcached/initialize_query.h libmemcached/instance.hpp \
	libmemcached/internal.h libmemcached/io.h libmemcached/io.hpp \
	libmemcached/is.h libmemcached/key.hpp \
	libmemcached/libmemcached_probes.h \
	libmemcached/memcached/protocol_binary.h \
	libmemcached/memcached/vbucket.h libmemcached/memory.h \
	libmemcached/namespace.h libmemcached/options.hpp \
	libmemcached/poll.h libmemcached/response.h \
	libmemcached/result.h libmemcached/sasl.hpp \
	libmemcached/server.hpp libmemcached/server_instance.h \
	libmemcached/socket.hpp libmemcached/string.hpp \
	libmemcached/udp.hpp libmemcached/version.hpp \
	libmemcached/virtual_bucket.h libmemcached/watchpoint.h \
	libmemcached/windows.hpp libtest/client.hpp \
	libtest/formatter.hpp libtest/timer.hpp libtest/alarm.h \
	libtest/binaries.h libtest/cpu.hpp libtest/blobslap_worker.h \
	libtest/callbacks.h libtest/dns.hpp libtest/cmdline.h \
	libtest/collection.h libtest/common.h libtest/comparison.hpp \
	libtest/core.h libtest/dream.h libtest/error.h \
	libtest/exception.hpp libtest/exception/disconnected.hpp \
	libtest/exception/fatal.hpp libtest/framework.h \
	libtest/gearmand.h libtest/drizzled.h libtest/get.h \
	libtest/has.hpp libtest/http.hpp libtest/is_pid.hpp \
	libtest/is_local.hpp libtest/killpid.h libtest/libtool.hpp \
	libtest/memcached.h libtest/memcached.hpp \
	libtest/poll_error.hpp libtest/port.h libtest/result.hpp \
	libtest/result/base.hpp libtest/result/fail.hpp \
	libtest/result/skip.hpp libtest/result/success.hpp \
	libtest/runner.h libtest/server.h libtest/server_container.h \
	libtest/signal.h libtest/socket.hpp libtest/stream.h \
	libtest/strerror.h libtest/string.hpp libtest/test.h \
	libtest/test.hpp libtest/thread.hpp libtest/tmpfile.hpp \
	libtest/lite.h libtest/valgrind.h libtest/vchar.hpp \
	libtest/version.h libtest/visibility.h libtest/wait.h \
	libtest/yatl.h clients/client_options.h clients/execute.h \
	clients/generator.h clients/ms_atomic.h clients/ms_conn.h \
	clients/ms_memslap.h clients/ms_setting.h clients/ms_sigsegv.h \
	clients/ms_stats.h clients/ms_task.h clients/ms_thread.h \
	clients/utilities.h example/byteorder.h \
	example/memcached_light.h example/storage.h \
	libmemcachedutil/common.h libmemcachedprotocol/ascii_handler.h \
	libmemcachedprotocol/binary_handler.h \
	libmemcachedprotocol/cache.h libmemcachedprotocol/common.h \
	tests/exist.h tests/hash_results.h tests/keys.hpp \
	tests/libmemcached_test_container.h tests/libmemcached_world.h \
	tests/libmemcached_world_socket.h tests/memc.hpp \
	tests/runner.h tests/basic.h tests/callbacks.h tests/debug.h \
	tests/deprecated.h tests/error_conditions.h tests/ketama.h \
	tests/ketama_test_cases.h tests/ketama_test_cases_spy.h \
	tests/libmemcached-1.0/all_tests.h \
	tests/libmemcached-1.0/callback_counter.h \
	tests/libmemcached-1.0/dump.h \
	tests/libmemcached-1.0/encoding_key.h \
	tests/libmemcached-1.0/fetch_all_results.h \
	tests/libmemcached-1.0/generate.h \
	tests/libmemcached-1.0/haldenbrand.h \
	tests/libmemcached-1.0/mem_functions.h \
	tests/libmemcached-1.0/memcached_get.h \
	tests/libmemcached-1.0/parser.h \
	tests/libmemcached-1.0/setup_and_teardowns.h \
	tests/libmemcached-1.0/stat.h tests/namespace.h tests/pool.h \
	tests/print.h tests/replication.h tests/server_add.h \
	tests/string.h tests/touch.h tests/virtual_buckets.h \
	util/daemon.hpp util/instance.hpp util/logfile.hpp \
	util/log.hpp util/operation.hpp util/signal.hpp \
	util/string.hpp util/pidfile.hpp win32/wrappers.h
HEADERS = $(include_HEADERS) $(nobase_include_HEADERS) \
	$(noinst_HEADERS)
am__tagged_files = $(HEADERS) $(SOURCES) $(TAGS_FILES) \
	$(LISP)mem_config.in
# Read a list of newline-separated strings from the standard input,
# and print each of them once, without duplicates.  Input order is
# *not* preserved.
am__uniquify_input = $(AWK) '\
  BEGIN { nonempty = 0; } \
  { items[$$0] = 1; nonempty = 1; } \
  END { if (nonempty) { for (i in items) print i; }; } \
'
# Make sure the list of sources is unique.  This is necessary because,
# e.g., the same source file might be shared among _SOURCES variables
# for different programs/libraries.
am__define_uniq_tagged_files = \
  list='$(am__tagged_files)'; \
  unique=`for i in $$list; do \
    if test -f "$$i"; then echo $$i; else echo $(srcdir)/$$i; fi; \
  done | $(am__uniquify_input)`
ETAGS = etags
CTAGS = ctags
CSCOPE = cscope
AM_RECURSIVE_TARGETS = cscope check recheck
am__tty_colors_dummy = \
  mgn= red= grn= lgn= blu= brg= std=; \
  am__color_tests=no
am__tty_colors = { \
  $(am__tty_colors_dummy); \
  if test "X$(AM_COLOR_TESTS)" = Xno; then \
    am__color_tests=no; \
  elif test "X$(AM_COLOR_TESTS)" = Xalways; then \
    am__color_tests=yes; \
  elif test "X$$TERM" != Xdumb && { test -t 1; } 2>/dev/null; then \
    am__color_tests=yes; \
  fi; \
  if test $$am__color_tests = yes; then \
    red='[0;31m'; \
    grn='[0;32m'; \
    lgn='[1;32m'; \
    blu='[1;34m'; \
    mgn='[0;35m'; \
    brg='[1m'; \
    std='[m'; \
  fi; \
}
am__recheck_rx = ^[ 	]*:recheck:[ 	]*
am__global_test_result_rx = ^[ 	]*:global-test-result:[ 	]*
am__copy_in_global_log_rx = ^[ 	]*:copy-in-global-log:[ 	]*
# A command that, given a newline-separated list of test names on the
# standard input, print the name of the tests that are to be re-run
# upon "make recheck".
am__list_recheck_tests = $(AWK) '{ \
  recheck = 1; \
  while ((rc = (getline line < ($$0 ".trs"))) != 0) \
    { \
      if (rc < 0) \
        { \
          if ((getline line2 < ($$0 ".log")) < 0) \
	    recheck = 0; \
          break; \
        } \
      else if (line ~ /$(am__recheck_rx)[nN][Oo]/) \
        { \
          recheck = 0; \
          break; \
        } \
      else if (line ~ /$(am__recheck_rx)[yY][eE][sS]/) \
        { \
          break; \
        } \
    }; \
  if (recheck) \
    print $$0; \
  close ($$0 ".trs"); \
  close ($$0 ".log"); \
}'
# A command that, given a newline-separated list of test names on the
# standard input, create the global log from their .trs and .log files.
am__create_global_log = $(AWK) ' \
function fatal(msg) \
{ \
  print "fatal: making $@: " msg | "cat >&2"; \
  exit 1; \
} \
function rst_section(header) \
{ \
  print header; \
  len = length(header); \
  for (i = 1; i <= len; i = i + 1) \
    printf "="; \
  printf "\n\n"; \
} \
{ \
  copy_in_global_log = 1; \
  global_test_result = "RUN"; \
  while ((rc = (getline line < ($$0 ".trs"))) != 0) \
    { \
      if (rc < 0) \
         fatal("failed to read from " $$0 ".trs"); \
      if (line ~ /$(am__global_test_result_rx)/) \
        { \
          sub("$(am__global_test_result_rx)", "", line); \
          sub("[ 	]*$$", "", line); \
          global_test_result = line; \
        } \
      else if (line ~ /$(am__copy_in_global_log_rx)[nN][oO]/) \
        copy_in_global_log = 0; \
    }; \
  if (copy_in_global_log) \
    { \
      rst_section(global_test_result ": " $$0); \
      while ((rc = (getline line < ($$0 ".log"))) != 0) \
      { \
        if (rc < 0) \
          fatal("failed to read from " $$0 ".log"); \
        print line; \
      }; \
      printf "\n"; \
    }; \
  close ($$0 ".trs"); \
  close ($$0 ".log"); \
}'
# Restructured Text title.
am__rst_title = { sed 's/.*/   &   /;h;s/./=/g;p;x;s/ *$$//;p;g' && echo; }
# Solaris 10 'make', and several other traditional 'make' implementations,
# pass "-e" to $(SHELL), and POSIX 2008 even requires this.  Work around it
# by disabling -e (using the XSI extension "set +e") if it's set.
am__sh_e_setup = case $$- in *e*) set +e;; esac
# Default flags passed to test drivers.
am__common_driver_flags = \
  --color-tests "$$am__color_tests" \
  --enable-hard-errors "$$am__enable_hard_errors" \
  --expect-failure "$$am__expect_failure"
