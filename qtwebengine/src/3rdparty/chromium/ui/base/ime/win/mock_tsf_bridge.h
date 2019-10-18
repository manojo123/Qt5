// Copyright 2018 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_BASE_IME_WIN_MOCK_TSF_BRIDGE_H_
#define UI_BASE_IME_WIN_MOCK_TSF_BRIDGE_H_

#include <msctf.h>
#include <wrl/client.h>

#include "base/compiler_specific.h"
#include "ui/base/ime/text_input_type.h"
#include "ui/base/ime/win/tsf_bridge.h"

namespace ui {

class MockTSFBridge : public TSFBridge {
 public:
  MockTSFBridge();
  ~MockTSFBridge() override;

  // TSFBridge:
  bool CancelComposition() override;
  bool ConfirmComposition() override;
  void OnTextInputTypeChanged(const TextInputClient* client) override;
  void OnTextLayoutChanged() override;
  void SetFocusedClient(HWND focused_window, TextInputClient* client) override;
  void RemoveFocusedClient(TextInputClient* client) override;
  Microsoft::WRL::ComPtr<ITfThreadMgr> GetThreadManager() override;
  TextInputClient* GetFocusedTextInputClient() const override;

  // Resets MockTSFBridge state including function call counter.
  void Reset();

  // Call count of EnableIME().
  unsigned enable_ime_call_count() const { return enable_ime_call_count_; }

  // Call count of DisableIME().
  unsigned disable_ime_call_count() const { return disable_ime_call_count_; }

  // Call count of CancelComposition().
  unsigned cancel_composition_call_count() const {
    return cancel_composition_call_count_;
  }

  // Call count of ConfirmComposition().
  unsigned confirm_composition_call_count() const {
    return confirm_composition_call_count_;
  }

  // Call count of OnTextLayoutChanged().
  unsigned on_text_layout_changed() const { return on_text_layout_changed_; }

  // Call count of AssociateFocus().
  unsigned associate_focus_call_count() const {
    return associate_focus_call_count_;
  }

  // Call count of SetFocusClient().
  unsigned set_focused_client_call_count() const {
    return set_focused_client_call_count_;
  }

  // Call count of RemoveFocusedClient().
  unsigned remove_focused_client_call_count() const {
    return remove_focused_client_call_count_;
  }

  // Returns current TextInputClient.
  TextInputClient* text_input_clinet() const { return text_input_client_; }

  // Returns currently focused window handle.
  HWND focused_window() const { return focused_window_; }

  // Returns latest text input type.
  TextInputType latest_text_iput_type() const {
    return latest_text_input_type_;
  }

 private:
  unsigned enable_ime_call_count_ = 0;
  unsigned disable_ime_call_count_ = 0;
  unsigned cancel_composition_call_count_ = 0;
  unsigned confirm_composition_call_count_ = 0;
  unsigned on_text_layout_changed_ = 0;
  unsigned associate_focus_call_count_ = 0;
  unsigned set_focused_client_call_count_ = 0;
  unsigned remove_focused_client_call_count_ = 0;
  TextInputClient* text_input_client_ = nullptr;
  HWND focused_window_ = nullptr;
  TextInputType latest_text_input_type_ = TEXT_INPUT_TYPE_NONE;
  Microsoft::WRL::ComPtr<ITfThreadMgr> thread_manager_;

  DISALLOW_COPY_AND_ASSIGN(MockTSFBridge);
};

}  // namespace ui

#endif  // UI_BASE_IME_WIN_MOCK_TSF_BRIDGE_H_