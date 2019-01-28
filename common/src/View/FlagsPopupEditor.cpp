/*
 Copyright (C) 2010-2017 Kristian Duske
 
 This file is part of TrenchBroom.
 
 TrenchBroom is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.
 
 TrenchBroom is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with TrenchBroom. If not, see <http://www.gnu.org/licenses/>.
 */

#include "FlagsPopupEditor.h"
#include "View/FlagsEditor.h"
#include "View/ViewConstants.h"
#include "View/PopupButton.h"

#include <QLabel>
#include <QHBoxLayout>

namespace TrenchBroom {
    namespace View {
        FlagsPopupEditor::FlagsPopupEditor(QWidget* parent, const size_t numCols, const QString& buttonLabel , const bool showFlagsText) :
        QWidget(parent),
        m_flagsTxt(nullptr),
        m_button(nullptr),
        m_editor(nullptr) {
            QWidget* flagsPanel = nullptr;
            if (showFlagsText) {
                flagsPanel = new QWidget();
                //flagsPanel->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_LISTBOX));
                
                m_flagsTxt = new QLabel();//flagsPanel, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT | wxST_ELLIPSIZE_END);
                
                auto* flagsPanelSizer = new QVBoxLayout();
                flagsPanelSizer->addStretch();
                flagsPanelSizer->addWidget(m_flagsTxt); //, 0, wxEXPAND | wxLEFT | wxRIGHT, LayoutConstants::TextBoxInnerMargin);
                flagsPanelSizer->addStretch();
                flagsPanel->setLayout(flagsPanelSizer);
            }
            
            m_button = new PopupButton(this, buttonLabel);
            m_button->setToolTip("Click to edit flags");
            
            auto* editorContainer = new QWidget(m_button->GetPopupWindow());//, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_SIMPLE);
            m_editor = new FlagsEditor(editorContainer, numCols);
            
            auto* editorContainerSizer = new QVBoxLayout();
            editorContainerSizer->addWidget(m_editor); //, 1, wxEXPAND | wxALL, LayoutConstants::DialogOuterMargin);
            editorContainer->setLayout(editorContainerSizer);
            
            auto* popupSizer = new QVBoxLayout();
            popupSizer->addWidget(editorContainer); //, 1, wxEXPAND);
            m_button->GetPopupWindow()->setLayout(popupSizer);
            
            auto* sizer = new QHBoxLayout();
            if (flagsPanel != nullptr) {
                sizer->addWidget(flagsPanel); //, 1, wxEXPAND);
                sizer->addSpacing(LayoutConstants::MediumHMargin);
            }
            sizer->addWidget(m_button, 0, Qt::AlignVCenter); //, 0, wxALIGN_CENTER_VERTICAL);
            setLayout(sizer);
            
            connect(m_editor, &FlagsEditor::flagChanged, this, [this](size_t index, int setFlag, int mixedFlag){
                updateFlagsText();
            });
            // forward this signal
            connect(m_editor, &FlagsEditor::flagChanged, this, &FlagsPopupEditor::flagChanged);
        }

        void FlagsPopupEditor::setFlags(const QStringList& labels, const QStringList& tooltips) {
            m_editor->setFlags(labels, tooltips);
            //m_button->GetPopupWindow()->Fit();
            updateFlagsText();
        }
        
        void FlagsPopupEditor::setFlags(const QList<int>& values, const QStringList& labels, const QStringList& tooltips) {
            m_editor->setFlags(values, labels, tooltips);
            //m_button->GetPopupWindow()->Fit();
            updateFlagsText();
        }

        void FlagsPopupEditor::setFlagValue(const int set, const int mixed) {
            m_editor->setFlagValue(set, mixed);
            updateFlagsText();
        }

        // FIXME: what exactly is this for?
#if 0
        bool FlagsPopupEditor::Enable(bool enable) {
            if (QWidget::Enable(enable)) {
                m_button->Enable(enable);
                updateFlagsText();
                return true;
            }
            return false;
        }
#endif
        
        void FlagsPopupEditor::updateFlagsText() {
            if (m_flagsTxt == nullptr)
                return;
            
            if (!isEnabled()) {
                m_flagsTxt->setDisabled(true);
                m_flagsTxt->setText("n/a");
                m_flagsTxt->setToolTip("");
                return;
            }
            
            QString label;
            bool first = true;
            bool mixed = false;
            for (size_t i = 0; i < m_editor->getNumFlags() && !mixed; ++i) {
                if (m_editor->isFlagMixed(i)) {
                    label = "multi";
                    mixed = true;
                } else if (m_editor->isFlagSet(i)) {
                    if (!first)
                        label += ", ";
                    label += m_editor->getFlagLabel(i);
                    first = false;
                }
            }
            
            m_flagsTxt->setText(label);
            if (!first)
                m_flagsTxt->setToolTip(label);
            else
                m_flagsTxt->setToolTip("");

            m_flagsTxt->setDisabled(mixed);

//            if (mixed)
//                m_flagsTxt->SetForegroundColour(Colors::disabledText());
//            else
//                m_flagsTxt->SetForegroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_BTNTEXT));
        }
    }
}
