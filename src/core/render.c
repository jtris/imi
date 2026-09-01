#include <stdio.h>
#include "render.h"
#include "core/section.h"


static void render_text(SectionResult *render_data, FILE *fp);


const OutputRenderer text_renderer = {
    .name = "text",
    .render = render_text,
};


static void render_text(SectionResult *render_data, FILE *fp)
{
    // TODO
    return;
}

