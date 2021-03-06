#include <assert.h>
#include <koio.h>
#include <stdint.h>
#include <stdio.h>
#include <chopsui/css.h>
#include <chopsui/host.h>
#include <chopsui/node.h>
#include <chopsui/render_node.h>
#include <chopsui/sui.h>
#include <chopsui/type.h>
#include <chopsui/util/errors.h>
#include <GLES2/gl2.h>

static void box_render(struct sui_node *node, uint32_t width, uint32_t height) {
	struct sui_scalar color;
	style_get_attr(node, "color", &color);
	assert(color.type == SCALAR_COLOR);
	glClearColor(
			color.r / 256.0,
			color.g / 256.0,
			color.b / 256.0,
			color.a / 256.0);
	glClear(GL_COLOR_BUFFER_BIT);
}

static struct render_node_impl box_render_impl = {
	.render = box_render,
};

struct attr_spec box_spec[] = {
	{ .key = "color", .spec = SCALAR_COLOR },
};

static void box_init(struct sui_node *node) {
	render_node_init(node, &box_render_impl);
}

static uint64_t box_attr_spec(const char *key) {
	return attr_spec_attr_spec(&box_spec, key);
}

static struct sui_type_impl box_impl = {
	.init = box_init,
	.attr_spec = box_attr_spec,
};

void koio_load_assets(void);

int main(int argc, char **argv) {
	koio_load_assets();
	type_impl_register("box", &box_impl);
	type_impl_register("box", &render_node_impl);
	struct sui_host *host = sui_host_initialize("basic-demo");
	struct sui_node *window = sui_load(ko_fopen("//window.sui", "r"), NULL);
	sui_host_show(host, window);
	sui_host_run(host);
	return 0;
}
