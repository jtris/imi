#ifndef RENDER_H
#define RENDER_H

#include <stdio.h>
#include "cli.h"
#include "core/section.h"


struct RendererFlags { bool verbose; };

typedef struct OutputRenderer {
    char *name;
    void (*render) (SectionResult *render_data, FILE *fp, struct RendererFlags flags);
} OutputRenderer;

extern const OutputRenderer text_renderer;
// TODO: implement json renderer

#endif
