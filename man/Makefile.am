EXTRA_DIST = manini.asciidoc

if HAVE_A2X
dir = $(top_srcdir)/man

man_MANS = $(dir)/manini.1
$(dir)/manini.1: asciidoc.stamp

asciidoc.stamp:
	$(A2X) -f manpage $(dir)/manini.asciidoc -v -v
	$(A2X) -fpdf $(dir)/manini.asciidoc -a revdate="`date`" -v -v

CLEANFILES = asciidoc.stamp
all-local: asciidoc.stamp
clean-local:
	rm -rf $(dir)/manini.1
	rm -rf manini.pdf

endif
