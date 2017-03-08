EXTRA_DIST = manini.asciidoc

if HAVE_A2X
dir = $(top_srcdir)/man

man_MANS = manini.1

manini.1:
	$(A2X) -f manpage manini.asciidoc

manini.pdf:
	$(A2X) -f pdf manini.asciidoc -a revdate="`date`"

CLEANFILES = manini.1 manini.pdf

all-local: manini.1
#           manini.pdf
clean-local:
	rm -rf $(dir)/manini.1
	rm -rf manini.pdf

endif
