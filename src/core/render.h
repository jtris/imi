#ifndef RENDER_H
#define RENDER_H

#include <stdio.h>
#include "core/section.h"


typedef struct OutputRenderer {
    char *name;
    void (*render) (SectionResult *render_data, FILE *fp);
} OutputRenderer;

extern const OutputRenderer text_renderer;
// TODO: implement json renderer

#endif
