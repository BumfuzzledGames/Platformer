#!/usr/bin/env ruby
require 'erb'

class String
    def camel_case
        gsub(/(.)([A-Z])/, '\1_\2').downcase
    end

    def c_ident
        gsub(/[^0-9a-z]/i, '_')
    end
end

lines = File.read(ARGV[0]).split("\n")
out = File.open(ARGV[1], "w+")

info_line = %r{
    info\s+
    face=(?<face>"[^"]*")\s+
    size=(?<size>\S*)\s+
    bold=(?<bold>\S*)\s+
    italic=(?<italic>\S*)\s+
    charset=(?<charset>"[^"]*")\s+
    unicode=(?<unicode>\S*)\s+
    stretchH=(?<stretchH>\S*)\s+
    smooth=(?<smooth>\S*)\s+
    aa=(?<aa>\S*)\s+
    padding=(?<padding>\S*)\s+
    spacing=(?<spacing>\S*)\s+
    outline=(?<outline>\S*)\s+
}x

common_line = %r{
    common\s+
    lineHeight=(?<lineHeight>\S*)\s+
    base=(?<base>\S*)\s+
    scaleW=(?<scaleW>\S*)\s+
    scaleH=(?<scaleH>\S*)\s+
    pages=(?<pages>\S*)\s+
    packed=(?<packed>\S*)\s+
    alphaChnl=(?<alphaChnl>\S*)\s+
    redChnl=(?<redChnl>\S*)\s+
    greenChnl=(?<greenChnl>\S*)\s+
    blueChnl=(?<blueChnl>\S*)
}x

page_line = %r{
    page\s+
    id=(?<id>\S*)\s+
    file="(?<file>[^"]*)"
}x

char_line = %r{
    char\s+
    id=(?<id>\S*)\s+
    x=(?<x>\S*)\s+
    y=(?<y>\S*)\s+
    width=(?<width>\S*)\s+
    height=(?<height>\S*)\s+
    xoffset=(?<xoffset>\S*)\s+
    yoffset=(?<yoffset>\S*)\s+
    xadvance=(?<xadvance>\S*)\s+
    page=(?<page>\S*)\s+
    chnl=(?<chnl>\S*)
}x

if lines.select{|l| page_line.match(l) }.compact.count != 1
    STDERR.puts "Only fonts with 1 page are supported"
    exit -1
end

template = <<ERB
#include "../src/font.h"

<%- lines.map{|l| page_line.match(l) }.compact.each do|l| -%>
extern SDL_Texture *data_<%= l[:file].c_ident %>_texture;
<%- end -%>

Font <%= ARGV[0].c_ident %> =
{
<%- lines.each do|line| -%>
    <%- if info_line =~ line -%>
        <%- $~.named_captures.each do|k,v| -%>
        <%- case k -%>
        <%- when 'padding', 'spacing' then %>    .<%= k.camel_case %> = { <%= v %> },
        <%- else                           %>    .<%= k.camel_case %> = <%= v %>,
        <%- end -%>
        <%- end -%>
    <%- elsif common_line =~ line -%>
        <%- $~.named_captures.each do|k,v| -%>
    .<%= k.camel_case %> = <%= v %>,
    <%- end %>
    <%- elsif page_line =~ line -%>
    .texture = &data_<%= $~[:file].c_ident %>_texture,
    <%- elsif char_line =~ line -%>
    .chars[<%= $~[:id]%>] = {
        .present = 1,
        .src = { <%= $~[:x] %>, <%= $~[:y] %>, <%= $~[:width] %>, <%= $~[:height] %> },
        .offset = { <%= $~[:xoffset] %>, <%= $~[:yoffset] %> },
        .advance = <%= $~[:xadvance] %>,
    },
    <%- end -%>
<%- end -%>
};
ERB

File.open(ARGV[1], "w+") do|f|
    f.write ERB.new(template, trim_mode:'-').result
end