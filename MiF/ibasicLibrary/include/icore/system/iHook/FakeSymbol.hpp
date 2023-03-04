/****
*
* Copyright(C) 2022 MiracleForest Studio. All Rights Reserved.
*
* @文件名：FakeSymbol.hpp
* @创建时间：2022.10.3.21:44
* @创建者：Lovelylavender4
* -----------------------------------------------------------------------------
*
* -----------------------------------------------------------------------------
* 如果你发现了bug，你可以去Github或邮箱(MiracleForest@Outlook.com)反馈给我们！
* 我们一定会努力做得更好的！
*
****/
#pragma once
//#define _USE_WINDOWS_H__

#include <icore/family/imacrofamily.h>
#include <icore/basic/iBasic.hpp>
#include <Demangler/include/MicrosoftDemangle.h>
#include <optional>
#include <string>

SPACE(i)
{
    SPACE(core)
    {
        SPACE(gadgets)
        {

            class gFakeSymbol
            {
            public:

                inline static llvm::ms_demangle::SpecialIntrinsicKind consumeSpecialIntrinsicKind(StringView& MangledName)
                {
                    using namespace llvm::ms_demangle;
                    using namespace llvm;
                    if (MangledName.consumeFront("?_7"))
                        return SpecialIntrinsicKind::Vftable;
                    if (MangledName.consumeFront("?_8"))
                        return SpecialIntrinsicKind::Vbtable;
                    if (MangledName.consumeFront("?_9"))
                        return SpecialIntrinsicKind::VcallThunk;
                    if (MangledName.consumeFront("?_A"))
                        return SpecialIntrinsicKind::Typeof;
                    if (MangledName.consumeFront("?_B"))
                        return SpecialIntrinsicKind::LocalStaticGuard;
                    if (MangledName.consumeFront("?_C"))
                        return SpecialIntrinsicKind::StringLiteralSymbol;
                    if (MangledName.consumeFront("?_P"))
                        return SpecialIntrinsicKind::UdtReturning;
                    if (MangledName.consumeFront("?_R0"))
                        return SpecialIntrinsicKind::RttiTypeDescriptor;
                    if (MangledName.consumeFront("?_R1"))
                        return SpecialIntrinsicKind::RttiBaseClassDescriptor;
                    if (MangledName.consumeFront("?_R2"))
                        return SpecialIntrinsicKind::RttiBaseClassArray;
                    if (MangledName.consumeFront("?_R3"))
                        return SpecialIntrinsicKind::RttiClassHierarchyDescriptor;
                    if (MangledName.consumeFront("?_R4"))
                        return SpecialIntrinsicKind::RttiCompleteObjLocator;
                    if (MangledName.consumeFront("?_S"))
                        return SpecialIntrinsicKind::LocalVftable;
                    if (MangledName.consumeFront("?__E"))
                        return SpecialIntrinsicKind::DynamicInitializer;
                    if (MangledName.consumeFront("?__F"))
                        return SpecialIntrinsicKind::DynamicAtexitDestructor;
                    if (MangledName.consumeFront("?__J"))
                        return SpecialIntrinsicKind::LocalStaticThreadGuard;
                    return SpecialIntrinsicKind::None;
                }

                // generate fakeSymbol for virtual functions
                inline static std::optional<std::string> getFakeSymbol(const std::string& fn)
                {
                    using namespace llvm::ms_demangle;
                    using namespace llvm;
                    Demangler Demangler;
                    StringView Name(fn.c_str());

                    if (!Name.startsWith('?'))
                        return std::nullopt;

                    Name.consumeFront('?');

                    SpecialIntrinsicKind SIK = consumeSpecialIntrinsicKind(Name);

                    if (SIK != SpecialIntrinsicKind::None)
                        return std::nullopt;

                    SymbolNode* DemangledName = Demangler.demangleDeclarator(Name);
                    if (DemangledName == nullptr || (DemangledName->kind() != NodeKind::FunctionSymbol && DemangledName->kind() != NodeKind::VariableSymbol) || Demangler.Error)
                        return std::nullopt;

                    if (DemangledName->kind() == NodeKind::FunctionSymbol)
                    {
                        auto& FunctionClass = ((FunctionSymbolNode*)DemangledName)->Signature->FunctionClass;
                        bool modified = false;
                        size_t originalSize = FunctionClass.toString().size();
                        if (FunctionClass.has(FC_Virtual))
                        {
                            FunctionClass.remove(FC_Virtual);
                            modified = true;
                        }
                        if (FunctionClass.has(FC_Protected))
                        {
                            FunctionClass.remove(FC_Protected);
                            FunctionClass.add(FC_Public);
                            modified = true;
                        }
                        if (FunctionClass.has(FC_Private))
                        {
                            FunctionClass.remove(FC_Private);
                            FunctionClass.add(FC_Public);
                            modified = true;
                        }
                        if (modified)
                        {
                            std::string FakeSymbol = fn;
                            std::string FakeFunctionClass = FunctionClass.toString();
                            size_t BeginPos = fn.size() - FunctionClass.pos->size();
                            FakeSymbol.erase(BeginPos, originalSize);
                            FakeSymbol.insert(BeginPos, FakeFunctionClass);
                            return FakeSymbol;
                        }
                    }

                    if (DemangledName->kind() == NodeKind::VariableSymbol)
                    {
                        auto& StorageClass = ((VariableSymbolNode*)DemangledName)->SC;
                        bool modified = false;
                        if (StorageClass == StorageClass::PrivateStatic)
                        {
                            StorageClass.set(StorageClass::PublicStatic);
                            modified = true;
                        }
                        if (StorageClass == StorageClass::ProtectedStatic)
                        {
                            StorageClass.set(StorageClass::PublicStatic);
                            modified = true;
                        }
                        if (modified)
                        {
                            std::string FakeSymbol = fn;
                            char FakeStorageClass = StorageClass.toChar();
                            size_t BeginPos = fn.size() - StorageClass.pos->size();
                            FakeSymbol[BeginPos] = FakeStorageClass;
                            return FakeSymbol;
                        }
                    }

                    return std::nullopt;
                }

            };//class gFakeSymbol

        }//SPACE(gadgets)
    }//SPACE(core)
}//SPACE(i)
