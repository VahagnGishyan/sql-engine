
// //////////////////////////////////////////////////////////////////////////
// //                                                                      //
// //////////////////////////////////////////////////////////////////////////

// #include "dyn-object.hpp"

// #include <fmt/core.h>

// #include <stdexcept>

// #include "utility/core.hpp"

// //////////////////////////////////////////////////////////////////////////
// //
// //////////////////////////////////////////////////////////////////////////

// namespace SQLEngine::TableNS
// {
//     //////////////////////////////////////////////////////////////////////
//     //                                                                  //
//     //////////////////////////////////////////////////////////////////////

//     auto DynamicObject::CopyObject() const -> Interface::UDynamicObject
//     {
//         auto&& obj    = std::make_unique<DynamicObject>();
//         obj->m_type   = GetType();
//         obj->m_pValue = CopyValue();
//         return std::move(obj);
//     }

//     auto DynamicObject::CopyValue() const -> Interface::UDynamicValue
//     {
//         return (m_pValue->CopyValue());
//     }

//     auto DynamicObject::IsNull() const -> bool
//     {
//         return (m_pValue == nullptr || m_pValue->IsNull());
//     }

//     //////////////////////////////////////////////////////////////////////
//     //                                                                  //
//     //////////////////////////////////////////////////////////////////////

//     auto DynamicObject::GetType() const -> const Interface::DynamicType&
//     {
//         return m_type;
//     }

//     void DynamicObject::SetType(const Interface::DynamicType& type)
//     {
//         m_type = type;
//     }

//     //////////////////////////////////////////////////////////////////////
//     //                                                                  //
//     //////////////////////////////////////////////////////////////////////

//     void DynamicObject::SetValue(const IDynamicObject& obj)
//     {
//         m_pValue->SetValue(obj.GetValue(), obj.GetType());
//     }
//     void DynamicObject::SetValueAsInt(const Interface::GetDynamicType<Interface::DynamicType::Int>::type& value)
//     {
//         SetType(Interface::DynamicType::Int);
//         m_pValue->SetValueAsInt(value);
//     }
//     void DynamicObject::SetValueAsDouble(const Interface::GetDynamicType<Interface::DynamicType::Double>::type& value)
//     {
//         SetType(Interface::DynamicType::Double);
//         m_pValue->SetValueAsDouble(value);
//     }
//     void DynamicObject::SetValueAsString(const Interface::GetDynamicType<Interface::DynamicType::String>::type& value)
//     {
//         SetType(Interface::DynamicType::String);
//         m_pValue->SetValueAsString(value);
//     }

//     //////////////////////////////////////////////////////////////////////
//     //                                                                  //
//     //////////////////////////////////////////////////////////////////////

//     auto DynamicObject::GetValue() const -> const Interface::IDynamicValue&
//     {
//         return *m_pValue;
//     }

//     auto DynamicObject::GetValueAsInt() const -> const Interface::GetDynamicType<Interface::DynamicType::Int>::type&
//     {
//         // AssertTypeIs(Interface::DynamicType::Int);
//         return m_pValue->GetValueAsInt();
//     }
//     auto DynamicObject::GetValueAsDouble() const
//         -> const Interface::GetDynamicType<Interface::DynamicType::Double>::type&
//     {
//         // AssertTypeIs(Interface::DynamicType::Double);
//         return m_pValue->GetValueAsDouble();
//     }
//     auto DynamicObject::GetValueAsString() const
//         -> const Interface::GetDynamicType<Interface::DynamicType::String>::type&
//     {
//         // AssertTypeIs(Interface::DynamicType::String);
//         return m_pValue->GetValueAsString();
//     }

//     //////////////////////////////////////////////////////////////////////
//     //                                                                  //
//     //////////////////////////////////////////////////////////////////////

//     void DynamicObject::AssertTypeIs(const Interface::DynamicType& type) const
//     {
//         Utility::Assert(
//             GetType() == type,
//             fmt::format("DynamicObject::AssertTypeIs(type: {}), types are different, this->type: {}",
//                         Interface::GetDynamicTypeNameAsString(type), Interface::GetDynamicTypeNameAsString(m_type)));
//     }
//     void DynamicObject::AssertTypeIsNot(const Interface::DynamicType& type) const
//     {
//         Utility::Assert(GetType() != type, fmt::format("DynamicObject::AssertTypeIsNot(type: {}), types are the same",
//                                                        Interface::GetDynamicTypeNameAsString(type)));
//     }

//     //////////////////////////////////////////////////////////////////////
//     //                                                                  //
//     //////////////////////////////////////////////////////////////////////

//     bool DynamicObject::Equal(const IDynamicObject& rhs)
//     {
//         AssertTypeIsNot(Interface::DynamicType::Double);
//         AssertTypeIs(rhs.GetType());

//         if (GetType() == Interface::DynamicType::String)
//         {
//             return this->GetValueAsString() == rhs.GetValueAsString();
//         }

//         if (GetType() == Interface::DynamicType::Int)
//         {
//             return this->GetValueAsInt() == rhs.GetValueAsInt();
//         }

//         Utility::Assert(false,
//                         fmt::format("DynamicObject::Equal(rhs.type: {}) this->type: {}, invalid types",
//                                     GetDynamicTypeNameAsString(rhs.GetType()), GetDynamicTypeNameAsString(GetType())));
//         return false;
//     }

//     bool DynamicObject::NotEqual(const IDynamicObject& element)
//     {
//         return (Equal(element) == false);
//     }

//     bool DynamicObject::GreaterThan(const IDynamicObject& rhs)
//     {
//         AssertTypeIsNot(Interface::DynamicType::String);
//         AssertTypeIs(rhs.GetType());

//         if (GetType() == Interface::DynamicType::Int)
//         {
//             return this->GetValueAsInt() > rhs.GetValueAsInt();
//         }

//         if (GetType() == Interface::DynamicType::Double)
//         {
//             return this->GetValueAsDouble() > rhs.GetValueAsDouble();
//         }

//         Utility::Assert(false,
//                         fmt::format("DynamicObject::GreaterThan(rhs.type: {}) this->type: {}, invalid types",
//                                     GetDynamicTypeNameAsString(rhs.GetType()), GetDynamicTypeNameAsString(GetType())));
//         return false;
//     }
//     bool DynamicObject::LessThan(const IDynamicObject& rhs)
//     {
//         return ((NotEqual(rhs)) && (!GreaterThan(rhs)));
//     }
//     bool DynamicObject::GreaterThanOrEqualTo(const IDynamicObject& rhs)
//     {
//         return (!LessThan(rhs));
//     }
//     bool DynamicObject::LessThanOrEqualTo(const IDynamicObject& rhs)
//     {
//         return (!GreaterThan(rhs));
//     }

//     //////////////////////////////////////////////////////////////////////
//     //                                                                  //
//     //////////////////////////////////////////////////////////////////////
// }  // namespace SQLEngine::TableNS

// //////////////////////////////////////////////////////////////////////////
// //                                                                      //
// //////////////////////////////////////////////////////////////////////////
