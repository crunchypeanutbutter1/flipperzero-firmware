#include "iso15693_3.h"
#include "iso15693_3_render.h"

// #include <nfc/protocols/iso15693_3/iso15693_3_poller.h>

#include "nfc/nfc_app_i.h"

#include "../nfc_protocol_support_gui_common.h"

static void nfc_scene_info_on_enter_iso15693_3(NfcApp* instance) {
    const NfcDevice* device = instance->nfc_device;
    const Iso15693_3Data* data = nfc_device_get_data(device, NfcProtocolIso15693_3);

    FuriString* temp_str = furi_string_alloc();
    furi_string_cat_printf(
        temp_str, "\e#%s\n", nfc_device_get_name(device, NfcDeviceNameTypeFull));
    nfc_render_iso15693_3_info(data, NfcProtocolFormatTypeFull, temp_str);

    widget_add_text_scroll_element(
        instance->widget, 0, 0, 128, 64, furi_string_get_cstr(temp_str));

    furi_string_free(temp_str);
}

// static NfcCommand
//     nfc_scene_read_poller_callback_iso15693_3(NfcGenericEvent event, void* context) {
//     furi_assert(event.protocol == NfcProtocolIso15693_3);
//
//     NfcApp* instance = context;
//     const Iso15693_3PollerEvent* iso15693_3_event = event.data;
//
//     if(iso15693_3_event->type == Iso15693_3PollerEventTypeReady) {
//         nfc_device_set_data(
//             instance->nfc_device, NfcProtocolIso15693_3, nfc_poller_get_data(instance->poller));
//         view_dispatcher_send_custom_event(instance->view_dispatcher, NfcCustomEventPollerSuccess);
//         return NfcCommandStop;
//     }
//
//     return NfcCommandContinue;
// }

static void nfc_scene_read_on_enter_iso15693_3(NfcApp* instance) {
    UNUSED(instance);
    // nfc_poller_start(instance->poller, nfc_scene_read_poller_callback_iso15693_3, instance);
}

static void nfc_scene_read_success_on_enter_iso15693_3(NfcApp* instance) {
    const NfcDevice* device = instance->nfc_device;
    const Iso15693_3Data* data = nfc_device_get_data(device, NfcProtocolIso15693_3);

    FuriString* temp_str = furi_string_alloc();
    furi_string_cat_printf(
        temp_str, "\e#%s\n", nfc_device_get_name(device, NfcDeviceNameTypeFull));
    nfc_render_iso15693_3_info(data, NfcProtocolFormatTypeShort, temp_str);

    widget_add_text_scroll_element(
        instance->widget, 0, 0, 128, 52, furi_string_get_cstr(temp_str));

    furi_string_free(temp_str);
}

static bool nfc_scene_info_on_event_iso15693_3(NfcApp* instance, uint32_t event) {
    if(event == GuiButtonTypeRight) {
        scene_manager_next_scene(instance->scene_manager, NfcSceneNotImplemented);
        return true;
    }

    return false;
}

static bool nfc_scene_saved_menu_on_event_iso15693_3(NfcApp* instance, uint32_t event) {
    if(event == SubmenuIndexCommonEdit) {
        scene_manager_next_scene(instance->scene_manager, NfcSceneSetUid);
        return true;
    }

    return false;
}

const NfcProtocolSupportBase nfc_protocol_support_iso15693_3 = {
    .features = NfcProtocolFeatureNone, // TODO: Implement better UID editing,

    .scene_info =
        {
            .on_enter = nfc_scene_info_on_enter_iso15693_3,
            .on_event = nfc_scene_info_on_event_iso15693_3,
        },
    .scene_read =
        {
            .on_enter = nfc_scene_read_on_enter_iso15693_3,
            .on_event = NULL,
        },
    .scene_read_menu =
        {
            .on_enter = nfc_protocol_support_common_on_enter_empty,
            .on_event = nfc_protocol_support_common_on_event_empty,
        },
    .scene_read_success =
        {
            .on_enter = nfc_scene_read_success_on_enter_iso15693_3,
            .on_event = NULL,
        },
    .scene_saved_menu =
        {
            .on_enter = nfc_protocol_support_common_on_enter_empty,
            .on_event = nfc_scene_saved_menu_on_event_iso15693_3,
        },
    .scene_emulate =
        {
            .on_enter = NULL,
            .on_event = NULL,
        },
};