#!/bin/sh

#dependecies
#apt-get install asciidoc dblatex
#edit /etc/asciidoc/dblatex/asciidoc-dblatex.xsl:

#<xsl:param name="doc.publisher.show">0</xsl:param>



a2x -fpdf manini.asciidoc -a revdate="`date`" -v -v
a2x -f manpage manini.asciidoc -v -v

