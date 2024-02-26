#include "include/placepicker2024/placepicker2024_plugin.h"

#include <flutter_linux/flutter_linux.h>
#include <gtk/gtk.h>
#include <sys/utsname.h>

#include <cstring>

#include "placepicker2024_plugin_private.h"

#define PLACEPICKER2024_PLUGIN(obj) \
  (G_TYPE_CHECK_INSTANCE_CAST((obj), placepicker2024_plugin_get_type(), \
                              Placepicker2024Plugin))

struct _Placepicker2024Plugin {
  GObject parent_instance;
};

G_DEFINE_TYPE(Placepicker2024Plugin, placepicker2024_plugin, g_object_get_type())

// Called when a method call is received from Flutter.
static void placepicker2024_plugin_handle_method_call(
    Placepicker2024Plugin* self,
    FlMethodCall* method_call) {
  g_autoptr(FlMethodResponse) response = nullptr;

  const gchar* method = fl_method_call_get_name(method_call);

  if (strcmp(method, "getPlatformVersion") == 0) {
    response = get_platform_version();
  } else {
    response = FL_METHOD_RESPONSE(fl_method_not_implemented_response_new());
  }

  fl_method_call_respond(method_call, response, nullptr);
}

FlMethodResponse* get_platform_version() {
  struct utsname uname_data = {};
  uname(&uname_data);
  g_autofree gchar *version = g_strdup_printf("Linux %s", uname_data.version);
  g_autoptr(FlValue) result = fl_value_new_string(version);
  return FL_METHOD_RESPONSE(fl_method_success_response_new(result));
}

static void placepicker2024_plugin_dispose(GObject* object) {
  G_OBJECT_CLASS(placepicker2024_plugin_parent_class)->dispose(object);
}

static void placepicker2024_plugin_class_init(Placepicker2024PluginClass* klass) {
  G_OBJECT_CLASS(klass)->dispose = placepicker2024_plugin_dispose;
}

static void placepicker2024_plugin_init(Placepicker2024Plugin* self) {}

static void method_call_cb(FlMethodChannel* channel, FlMethodCall* method_call,
                           gpointer user_data) {
  Placepicker2024Plugin* plugin = PLACEPICKER2024_PLUGIN(user_data);
  placepicker2024_plugin_handle_method_call(plugin, method_call);
}

void placepicker2024_plugin_register_with_registrar(FlPluginRegistrar* registrar) {
  Placepicker2024Plugin* plugin = PLACEPICKER2024_PLUGIN(
      g_object_new(placepicker2024_plugin_get_type(), nullptr));

  g_autoptr(FlStandardMethodCodec) codec = fl_standard_method_codec_new();
  g_autoptr(FlMethodChannel) channel =
      fl_method_channel_new(fl_plugin_registrar_get_messenger(registrar),
                            "placepicker2024",
                            FL_METHOD_CODEC(codec));
  fl_method_channel_set_method_call_handler(channel, method_call_cb,
                                            g_object_ref(plugin),
                                            g_object_unref);

  g_object_unref(plugin);
}
