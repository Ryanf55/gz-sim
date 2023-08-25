/*
 * Copyright (C) 2023 Open Source Robotics Foundation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#ifndef GZ_GUI_APPLYFORCETORQUE_HH_
#define GZ_GUI_APPLYFORCETORQUE_HH_

#include <memory>

#include <QString>
#include <QStringList>
#include <QObject>
#include <QEvent>

#include <gz/sim/EntityComponentManager.hh>
#include <gz/sim/gui/GuiSystem.hh>

namespace gz
{
namespace sim
{
  class ApplyForceTorquePrivate;

  /// \brief Publish wrench to "/world/<world_name>/wrench" topic.
  /// Automatically loads the ApplyLinkWrench system.
  ///
  /// ## Configuration
  /// This plugin doesn't accept any custom configuration.
  class ApplyForceTorque : public gz::sim::GuiSystem
  {
    Q_OBJECT

    /// \brief Model name
    Q_PROPERTY(
      QString modelName
      READ ModelName
      NOTIFY ModelNameChanged
    )

    /// \brief Link list
    Q_PROPERTY(
      QStringList linkNameList
      READ LinkNameList
      NOTIFY LinkNameListChanged
    )

    /// \brief Link index
    Q_PROPERTY(
      int linkIndex
      READ LinkIndex
      WRITE SetLinkIndex
      NOTIFY LinkIndexChanged
    )

    /// \brief Force
    Q_PROPERTY(
      QVector3D force
      READ Force
      WRITE SetForce
      NOTIFY ForceChanged
    )

    /// \brief Torque
    Q_PROPERTY(
      QVector3D torque
      READ Torque
      WRITE SetTorque
      NOTIFY TorqueChanged
    )

    /// \brief Constructor
    public: ApplyForceTorque();

    /// \brief Destructor
    public: ~ApplyForceTorque() override;

    // Documentation inherited
    public: void LoadConfig(const tinyxml2::XMLElement *_pluginElem) override;

    // Documentation inherited
    protected: bool eventFilter(QObject *_obj, QEvent *_event) override;

    // Documentation inherited
    public: void Update(const UpdateInfo &_info,
      EntityComponentManager &_ecm) override;

    /// \brief Get the name of the selected model
    public: Q_INVOKABLE QString ModelName() const;

    /// \brief Notify that the model name changed
    signals: void ModelNameChanged();

    /// \brief Get the name of the links of the selected model
    public: Q_INVOKABLE QStringList LinkNameList() const;

    /// \brief Notify that the link list changed
    signals: void LinkNameListChanged();

    /// \brief Get index of the link in the list
    public: Q_INVOKABLE int LinkIndex() const;

    /// \brief Notify that the link index changed
    signals: void LinkIndexChanged();

    /// \brief Set the index of the link in the list
    public: Q_INVOKABLE void SetLinkIndex(int _linkIndex);

    /// \brief Get the force vector
    /// \return The force vector
    public: Q_INVOKABLE QVector3D Force() const;

    /// \brief Notify that the force changed
    signals: void ForceChanged();

    /// \brief Set the force vector
    /// \param[in] _force The new force vector
    public: Q_INVOKABLE void SetForce(QVector3D _force);

    /// \brief Get the torque vector
    /// \return The torque vector
    public: Q_INVOKABLE QVector3D Torque() const;

    /// \brief Notify that the torque changed
    signals: void TorqueChanged();

    /// \brief Set the torque vector
    /// \param[in] _torque The new torque vector
    public: Q_INVOKABLE void SetTorque(QVector3D _torque);

    /// \brief Apply the specified force
    public: Q_INVOKABLE void ApplyForce();

    /// \brief Apply the specified torque
    public: Q_INVOKABLE void ApplyTorque();

    /// \brief Apply the specified force and torque
    public: Q_INVOKABLE void ApplyAll();

    /// \internal
    /// \brief Pointer to private data.
    private: std::unique_ptr<ApplyForceTorquePrivate> dataPtr;
  };
}
}

#endif
