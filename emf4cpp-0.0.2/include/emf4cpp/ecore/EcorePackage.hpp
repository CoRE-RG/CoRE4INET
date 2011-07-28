// -*- mode: c++; c-basic-style: "bsd"; c-basic-offset: 4; -*-
/*
 * ecore/EcorePackage.hpp
 * Copyright (C) Cátedra SAES-UMU 2010 <andres.senac@um.es>
 *
 * EMF4CPP is free software: you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published
 * by the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * EMF4CPP is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _ECOREPACKAGE_HPP
#define _ECOREPACKAGE_HPP

#include <ecore/EPackage.hpp>
#include <ecore_forward.hpp>

namespace ecore
{

    class EcorePackage: public virtual ::ecore::EPackage
    {
    public:

        static EcorePackage_ptr _instance();

        // IDs for classifiers

        static const int EANNOTATION = 0;

        static const int EATTRIBUTE = 1;

        static const int EBIGDECIMAL = 2;

        static const int EBIGINTEGER = 3;

        static const int EBOOLEAN = 4;

        static const int EBOOLEANOBJECT = 5;

        static const int EBYTE = 6;

        static const int EBYTEARRAY = 7;

        static const int EBYTEOBJECT = 8;

        static const int ECHAR = 9;

        static const int ECHARACTEROBJECT = 10;

        static const int ECLASS = 11;

        static const int ECLASSIFIER = 12;

        static const int EDATATYPE = 13;

        static const int EDATE = 14;

        static const int EDIAGNOSTICCHAIN = 15;

        static const int EDOUBLE = 16;

        static const int EDOUBLEOBJECT = 17;

        static const int EELIST = 18;

        static const int EENUM = 19;

        static const int EENUMERATOR = 20;

        static const int EENUMLITERAL = 21;

        static const int EFACTORY = 22;

        static const int EFEATUREMAP = 23;

        static const int EFEATUREMAPENTRY = 24;

        static const int EFLOAT = 25;

        static const int EFLOATOBJECT = 26;

        static const int EGENERICTYPE = 27;

        static const int EINT = 28;

        static const int EINTEGEROBJECT = 29;

        static const int EINVOCATIONTARGETEXCEPTION = 30;

        static const int EJAVACLASS = 31;

        static const int EJAVAOBJECT = 32;

        static const int ELONG = 33;

        static const int ELONGOBJECT = 34;

        static const int EMAP = 35;

        static const int EMODELELEMENT = 36;

        static const int ENAMEDELEMENT = 37;

        static const int EOBJECT = 38;

        static const int EOPERATION = 39;

        static const int EPACKAGE = 40;

        static const int EPARAMETER = 41;

        static const int EREFERENCE = 42;

        static const int ERESOURCE = 43;

        static const int ERESOURCESET = 44;

        static const int ESHORT = 45;

        static const int ESHORTOBJECT = 46;

        static const int ESTRING = 47;

        static const int ESTRINGTOSTRINGMAPENTRY = 48;

        static const int ESTRUCTURALFEATURE = 49;

        static const int ETREEITERATOR = 50;

        static const int ETYPEDELEMENT = 51;

        static const int ETYPEPARAMETER = 52;

        static const int EATTRIBUTE__ID = 0;

        static const int EATTRIBUTE__EATTRIBUTETYPE = 1;

        static const int EANNOTATION__SOURCE = 2;

        static const int EANNOTATION__DETAILS = 3;

        static const int EANNOTATION__EMODELELEMENT = 4;

        static const int EANNOTATION__CONTENTS = 5;

        static const int EANNOTATION__REFERENCES = 6;

        static const int ECLASS__ABSTRACT = 7;

        static const int ECLASS__INTERFACE = 8;

        static const int ECLASS__ESUPERTYPES = 9;

        static const int ECLASS__EOPERATIONS = 10;

        static const int ECLASS__EALLATTRIBUTES = 11;

        static const int ECLASS__EALLREFERENCES = 12;

        static const int ECLASS__EREFERENCES = 13;

        static const int ECLASS__EATTRIBUTES = 14;

        static const int ECLASS__EALLCONTAINMENTS = 15;

        static const int ECLASS__EALLOPERATIONS = 16;

        static const int ECLASS__EALLSTRUCTURALFEATURES = 17;

        static const int ECLASS__EALLSUPERTYPES = 18;

        static const int ECLASS__EIDATTRIBUTE = 19;

        static const int ECLASS__ESTRUCTURALFEATURES = 20;

        static const int ECLASS__EGENERICSUPERTYPES = 21;

        static const int ECLASS__EALLGENERICSUPERTYPES = 22;

        static const int ECLASSIFIER__INSTANCECLASSNAME = 23;

        static const int ECLASSIFIER__INSTANCECLASS = 24;

        static const int ECLASSIFIER__DEFAULTVALUE = 25;

        static const int ECLASSIFIER__INSTANCETYPENAME = 26;

        static const int ECLASSIFIER__EPACKAGE = 27;

        static const int ECLASSIFIER__ETYPEPARAMETERS = 28;

        static const int EDATATYPE__SERIALIZABLE = 29;

        static const int EENUM__ELITERALS = 30;

        static const int EENUMLITERAL__VALUE = 31;

        static const int EENUMLITERAL__INSTANCE = 32;

        static const int EENUMLITERAL__LITERAL = 33;

        static const int EENUMLITERAL__EENUM = 34;

        static const int EFACTORY__EPACKAGE = 35;

        static const int EMODELELEMENT__EANNOTATIONS = 36;

        static const int ENAMEDELEMENT__NAME = 37;

        static const int EOPERATION__ECONTAININGCLASS = 38;

        static const int EOPERATION__ETYPEPARAMETERS = 39;

        static const int EOPERATION__EPARAMETERS = 40;

        static const int EOPERATION__EEXCEPTIONS = 41;

        static const int EOPERATION__EGENERICEXCEPTIONS = 42;

        static const int EPACKAGE__NSURI = 43;

        static const int EPACKAGE__NSPREFIX = 44;

        static const int EPACKAGE__EFACTORYINSTANCE = 45;

        static const int EPACKAGE__ECLASSIFIERS = 46;

        static const int EPACKAGE__ESUBPACKAGES = 47;

        static const int EPACKAGE__ESUPERPACKAGE = 48;

        static const int EPARAMETER__EOPERATION = 49;

        static const int EREFERENCE__CONTAINMENT = 50;

        static const int EREFERENCE__CONTAINER = 51;

        static const int EREFERENCE__RESOLVEPROXIES = 52;

        static const int EREFERENCE__EOPPOSITE = 53;

        static const int EREFERENCE__EREFERENCETYPE = 54;

        static const int EREFERENCE__EKEYS = 55;

        static const int ESTRUCTURALFEATURE__CHANGEABLE = 56;

        static const int ESTRUCTURALFEATURE__VOLATILE = 57;

        static const int ESTRUCTURALFEATURE__TRANSIENT = 58;

        static const int ESTRUCTURALFEATURE__DEFAULTVALUELITERAL = 59;

        static const int ESTRUCTURALFEATURE__DEFAULTVALUE = 60;

        static const int ESTRUCTURALFEATURE__UNSETTABLE = 61;

        static const int ESTRUCTURALFEATURE__DERIVED = 62;

        static const int ESTRUCTURALFEATURE__ECONTAININGCLASS = 63;

        static const int ETYPEDELEMENT__ORDERED = 64;

        static const int ETYPEDELEMENT__UNIQUE = 65;

        static const int ETYPEDELEMENT__LOWERBOUND = 66;

        static const int ETYPEDELEMENT__UPPERBOUND = 67;

        static const int ETYPEDELEMENT__MANY = 68;

        static const int ETYPEDELEMENT__REQUIRED = 69;

        static const int ETYPEDELEMENT__ETYPE = 70;

        static const int ETYPEDELEMENT__EGENERICTYPE = 71;

        static const int ESTRINGTOSTRINGMAPENTRY__KEY = 72;

        static const int ESTRINGTOSTRINGMAPENTRY__VALUE = 73;

        static const int EGENERICTYPE__EUPPERBOUND = 74;

        static const int EGENERICTYPE__ETYPEARGUMENTS = 75;

        static const int EGENERICTYPE__ERAWTYPE = 76;

        static const int EGENERICTYPE__ELOWERBOUND = 77;

        static const int EGENERICTYPE__ETYPEPARAMETER = 78;

        static const int EGENERICTYPE__ECLASSIFIER = 79;

        static const int ETYPEPARAMETER__EBOUNDS = 80;

        // IDs for classifiers for class EAnnotation 

        static const int EANNOTATION__EANNOTATIONS =
                EMODELELEMENT__EANNOTATIONS;

        // IDs for classifiers for class EAttribute 

        static const int EATTRIBUTE__EANNOTATIONS = EMODELELEMENT__EANNOTATIONS;

        static const int EATTRIBUTE__NAME = ENAMEDELEMENT__NAME;

        static const int EATTRIBUTE__ORDERED = ETYPEDELEMENT__ORDERED;

        static const int EATTRIBUTE__UNIQUE = ETYPEDELEMENT__UNIQUE;

        static const int EATTRIBUTE__LOWERBOUND = ETYPEDELEMENT__LOWERBOUND;

        static const int EATTRIBUTE__UPPERBOUND = ETYPEDELEMENT__UPPERBOUND;

        static const int EATTRIBUTE__MANY = ETYPEDELEMENT__MANY;

        static const int EATTRIBUTE__REQUIRED = ETYPEDELEMENT__REQUIRED;

        static const int EATTRIBUTE__ETYPE = ETYPEDELEMENT__ETYPE;

        static const int EATTRIBUTE__EGENERICTYPE = ETYPEDELEMENT__EGENERICTYPE;

        static const int EATTRIBUTE__CHANGEABLE =
                ESTRUCTURALFEATURE__CHANGEABLE;

        static const int EATTRIBUTE__VOLATILE = ESTRUCTURALFEATURE__VOLATILE;

        static const int EATTRIBUTE__TRANSIENT = ESTRUCTURALFEATURE__TRANSIENT;

        static const int EATTRIBUTE__DEFAULTVALUELITERAL =
                ESTRUCTURALFEATURE__DEFAULTVALUELITERAL;

        static const int EATTRIBUTE__DEFAULTVALUE =
                ESTRUCTURALFEATURE__DEFAULTVALUE;

        static const int EATTRIBUTE__UNSETTABLE =
                ESTRUCTURALFEATURE__UNSETTABLE;

        static const int EATTRIBUTE__DERIVED = ESTRUCTURALFEATURE__DERIVED;

        static const int EATTRIBUTE__ECONTAININGCLASS =
                ESTRUCTURALFEATURE__ECONTAININGCLASS;

        // IDs for classifiers for class EClass 

        static const int ECLASS__EANNOTATIONS = EMODELELEMENT__EANNOTATIONS;

        static const int ECLASS__NAME = ENAMEDELEMENT__NAME;

        static const int ECLASS__INSTANCECLASSNAME =
                ECLASSIFIER__INSTANCECLASSNAME;

        static const int ECLASS__INSTANCECLASS = ECLASSIFIER__INSTANCECLASS;

        static const int ECLASS__DEFAULTVALUE = ECLASSIFIER__DEFAULTVALUE;

        static const int ECLASS__INSTANCETYPENAME =
                ECLASSIFIER__INSTANCETYPENAME;

        static const int ECLASS__EPACKAGE = ECLASSIFIER__EPACKAGE;

        static const int ECLASS__ETYPEPARAMETERS = ECLASSIFIER__ETYPEPARAMETERS;

        // IDs for classifiers for class EClassifier 

        static const int ECLASSIFIER__EANNOTATIONS =
                EMODELELEMENT__EANNOTATIONS;

        static const int ECLASSIFIER__NAME = ENAMEDELEMENT__NAME;

        // IDs for classifiers for class EDataType 

        static const int EDATATYPE__EANNOTATIONS = EMODELELEMENT__EANNOTATIONS;

        static const int EDATATYPE__NAME = ENAMEDELEMENT__NAME;

        static const int EDATATYPE__INSTANCECLASSNAME =
                ECLASSIFIER__INSTANCECLASSNAME;

        static const int EDATATYPE__INSTANCECLASS = ECLASSIFIER__INSTANCECLASS;

        static const int EDATATYPE__DEFAULTVALUE = ECLASSIFIER__DEFAULTVALUE;

        static const int EDATATYPE__INSTANCETYPENAME =
                ECLASSIFIER__INSTANCETYPENAME;

        static const int EDATATYPE__EPACKAGE = ECLASSIFIER__EPACKAGE;

        static const int EDATATYPE__ETYPEPARAMETERS =
                ECLASSIFIER__ETYPEPARAMETERS;

        // IDs for classifiers for class EEnum 

        static const int EENUM__EANNOTATIONS = EMODELELEMENT__EANNOTATIONS;

        static const int EENUM__NAME = ENAMEDELEMENT__NAME;

        static const int EENUM__INSTANCECLASSNAME =
                ECLASSIFIER__INSTANCECLASSNAME;

        static const int EENUM__INSTANCECLASS = ECLASSIFIER__INSTANCECLASS;

        static const int EENUM__DEFAULTVALUE = ECLASSIFIER__DEFAULTVALUE;

        static const int EENUM__INSTANCETYPENAME =
                ECLASSIFIER__INSTANCETYPENAME;

        static const int EENUM__EPACKAGE = ECLASSIFIER__EPACKAGE;

        static const int EENUM__ETYPEPARAMETERS = ECLASSIFIER__ETYPEPARAMETERS;

        static const int EENUM__SERIALIZABLE = EDATATYPE__SERIALIZABLE;

        // IDs for classifiers for class EEnumLiteral 

        static const int EENUMLITERAL__EANNOTATIONS =
                EMODELELEMENT__EANNOTATIONS;

        static const int EENUMLITERAL__NAME = ENAMEDELEMENT__NAME;

        // IDs for classifiers for class EFactory 

        static const int EFACTORY__EANNOTATIONS = EMODELELEMENT__EANNOTATIONS;

        // IDs for classifiers for class EGenericType 


        // IDs for classifiers for class EModelElement 


        // IDs for classifiers for class ENamedElement 

        static const int ENAMEDELEMENT__EANNOTATIONS =
                EMODELELEMENT__EANNOTATIONS;

        // IDs for classifiers for class EObject 


        // IDs for classifiers for class EOperation 

        static const int EOPERATION__EANNOTATIONS = EMODELELEMENT__EANNOTATIONS;

        static const int EOPERATION__NAME = ENAMEDELEMENT__NAME;

        static const int EOPERATION__ORDERED = ETYPEDELEMENT__ORDERED;

        static const int EOPERATION__UNIQUE = ETYPEDELEMENT__UNIQUE;

        static const int EOPERATION__LOWERBOUND = ETYPEDELEMENT__LOWERBOUND;

        static const int EOPERATION__UPPERBOUND = ETYPEDELEMENT__UPPERBOUND;

        static const int EOPERATION__MANY = ETYPEDELEMENT__MANY;

        static const int EOPERATION__REQUIRED = ETYPEDELEMENT__REQUIRED;

        static const int EOPERATION__ETYPE = ETYPEDELEMENT__ETYPE;

        static const int EOPERATION__EGENERICTYPE = ETYPEDELEMENT__EGENERICTYPE;

        // IDs for classifiers for class EPackage 

        static const int EPACKAGE__EANNOTATIONS = EMODELELEMENT__EANNOTATIONS;

        static const int EPACKAGE__NAME = ENAMEDELEMENT__NAME;

        // IDs for classifiers for class EParameter 

        static const int EPARAMETER__EANNOTATIONS = EMODELELEMENT__EANNOTATIONS;

        static const int EPARAMETER__NAME = ENAMEDELEMENT__NAME;

        static const int EPARAMETER__ORDERED = ETYPEDELEMENT__ORDERED;

        static const int EPARAMETER__UNIQUE = ETYPEDELEMENT__UNIQUE;

        static const int EPARAMETER__LOWERBOUND = ETYPEDELEMENT__LOWERBOUND;

        static const int EPARAMETER__UPPERBOUND = ETYPEDELEMENT__UPPERBOUND;

        static const int EPARAMETER__MANY = ETYPEDELEMENT__MANY;

        static const int EPARAMETER__REQUIRED = ETYPEDELEMENT__REQUIRED;

        static const int EPARAMETER__ETYPE = ETYPEDELEMENT__ETYPE;

        static const int EPARAMETER__EGENERICTYPE = ETYPEDELEMENT__EGENERICTYPE;

        // IDs for classifiers for class EReference 

        static const int EREFERENCE__EANNOTATIONS = EMODELELEMENT__EANNOTATIONS;

        static const int EREFERENCE__NAME = ENAMEDELEMENT__NAME;

        static const int EREFERENCE__ORDERED = ETYPEDELEMENT__ORDERED;

        static const int EREFERENCE__UNIQUE = ETYPEDELEMENT__UNIQUE;

        static const int EREFERENCE__LOWERBOUND = ETYPEDELEMENT__LOWERBOUND;

        static const int EREFERENCE__UPPERBOUND = ETYPEDELEMENT__UPPERBOUND;

        static const int EREFERENCE__MANY = ETYPEDELEMENT__MANY;

        static const int EREFERENCE__REQUIRED = ETYPEDELEMENT__REQUIRED;

        static const int EREFERENCE__ETYPE = ETYPEDELEMENT__ETYPE;

        static const int EREFERENCE__EGENERICTYPE = ETYPEDELEMENT__EGENERICTYPE;

        static const int EREFERENCE__CHANGEABLE =
                ESTRUCTURALFEATURE__CHANGEABLE;

        static const int EREFERENCE__VOLATILE = ESTRUCTURALFEATURE__VOLATILE;

        static const int EREFERENCE__TRANSIENT = ESTRUCTURALFEATURE__TRANSIENT;

        static const int EREFERENCE__DEFAULTVALUELITERAL =
                ESTRUCTURALFEATURE__DEFAULTVALUELITERAL;

        static const int EREFERENCE__DEFAULTVALUE =
                ESTRUCTURALFEATURE__DEFAULTVALUE;

        static const int EREFERENCE__UNSETTABLE =
                ESTRUCTURALFEATURE__UNSETTABLE;

        static const int EREFERENCE__DERIVED = ESTRUCTURALFEATURE__DERIVED;

        static const int EREFERENCE__ECONTAININGCLASS =
                ESTRUCTURALFEATURE__ECONTAININGCLASS;

        // IDs for classifiers for class EStringToStringMapEntry 


        // IDs for classifiers for class EStructuralFeature 

        static const int ESTRUCTURALFEATURE__EANNOTATIONS =
                EMODELELEMENT__EANNOTATIONS;

        static const int ESTRUCTURALFEATURE__NAME = ENAMEDELEMENT__NAME;

        static const int ESTRUCTURALFEATURE__ORDERED = ETYPEDELEMENT__ORDERED;

        static const int ESTRUCTURALFEATURE__UNIQUE = ETYPEDELEMENT__UNIQUE;

        static const int ESTRUCTURALFEATURE__LOWERBOUND =
                ETYPEDELEMENT__LOWERBOUND;

        static const int ESTRUCTURALFEATURE__UPPERBOUND =
                ETYPEDELEMENT__UPPERBOUND;

        static const int ESTRUCTURALFEATURE__MANY = ETYPEDELEMENT__MANY;

        static const int ESTRUCTURALFEATURE__REQUIRED = ETYPEDELEMENT__REQUIRED;

        static const int ESTRUCTURALFEATURE__ETYPE = ETYPEDELEMENT__ETYPE;

        static const int ESTRUCTURALFEATURE__EGENERICTYPE =
                ETYPEDELEMENT__EGENERICTYPE;

        // IDs for classifiers for class ETypedElement 

        static const int ETYPEDELEMENT__EANNOTATIONS =
                EMODELELEMENT__EANNOTATIONS;

        static const int ETYPEDELEMENT__NAME = ENAMEDELEMENT__NAME;

        // IDs for classifiers for class ETypeParameter 

        static const int ETYPEPARAMETER__EANNOTATIONS =
                EMODELELEMENT__EANNOTATIONS;

        static const int ETYPEPARAMETER__NAME = ENAMEDELEMENT__NAME;

        // EClassifiers methods

        virtual ::ecore::EClass_ptr getEAttribute();

        virtual ::ecore::EClass_ptr getEAnnotation_();

        virtual ::ecore::EClass_ptr getEClass();

        virtual ::ecore::EClass_ptr getEClassifier_();

        virtual ::ecore::EClass_ptr getEDataType();

        virtual ::ecore::EClass_ptr getEEnum();

        virtual ::ecore::EClass_ptr getEEnumLiteral();

        virtual ::ecore::EClass_ptr getEFactory();

        virtual ::ecore::EClass_ptr getEModelElement();

        virtual ::ecore::EClass_ptr getENamedElement();

        virtual ::ecore::EClass_ptr getEObject();

        virtual ::ecore::EClass_ptr getEOperation();

        virtual ::ecore::EClass_ptr getEPackage();

        virtual ::ecore::EClass_ptr getEParameter();

        virtual ::ecore::EClass_ptr getEReference();

        virtual ::ecore::EClass_ptr getEStructuralFeature();

        virtual ::ecore::EClass_ptr getETypedElement();

        virtual ::ecore::EDataType_ptr getEBigDecimal();

        virtual ::ecore::EDataType_ptr getEBigInteger();

        virtual ::ecore::EDataType_ptr getEBoolean();

        virtual ::ecore::EDataType_ptr getEBooleanObject();

        virtual ::ecore::EDataType_ptr getEByte();

        virtual ::ecore::EDataType_ptr getEByteArray();

        virtual ::ecore::EDataType_ptr getEByteObject();

        virtual ::ecore::EDataType_ptr getEChar();

        virtual ::ecore::EDataType_ptr getECharacterObject();

        virtual ::ecore::EDataType_ptr getEDate();

        virtual ::ecore::EDataType_ptr getEDiagnosticChain();

        virtual ::ecore::EDataType_ptr getEDouble();

        virtual ::ecore::EDataType_ptr getEDoubleObject();

        virtual ::ecore::EDataType_ptr getEEList();

        virtual ::ecore::EDataType_ptr getEEnumerator();

        virtual ::ecore::EDataType_ptr getEFeatureMap();

        virtual ::ecore::EDataType_ptr getEFeatureMapEntry();

        virtual ::ecore::EDataType_ptr getEFloat();

        virtual ::ecore::EDataType_ptr getEFloatObject();

        virtual ::ecore::EDataType_ptr getEInt();

        virtual ::ecore::EDataType_ptr getEIntegerObject();

        virtual ::ecore::EDataType_ptr getEJavaClass();

        virtual ::ecore::EDataType_ptr getEJavaObject();

        virtual ::ecore::EDataType_ptr getELong();

        virtual ::ecore::EDataType_ptr getELongObject();

        virtual ::ecore::EDataType_ptr getEMap();

        virtual ::ecore::EDataType_ptr getEResource();

        virtual ::ecore::EDataType_ptr getEResourceSet();

        virtual ::ecore::EDataType_ptr getEShort();

        virtual ::ecore::EDataType_ptr getEShortObject();

        virtual ::ecore::EDataType_ptr getEString();

        virtual ::ecore::EClass_ptr getEStringToStringMapEntry();

        virtual ::ecore::EDataType_ptr getETreeIterator();

        virtual ::ecore::EClass_ptr getEGenericType();

        virtual ::ecore::EClass_ptr getETypeParameter();

        virtual ::ecore::EDataType_ptr getEInvocationTargetException();

        // EStructuralFeatures methods

        virtual ::ecore::EReference_ptr getEModelElement__eAnnotations();

        virtual ::ecore::EAttribute_ptr getENamedElement__name();

        virtual ::ecore::EAttribute_ptr getETypedElement__ordered();

        virtual ::ecore::EAttribute_ptr getETypedElement__unique();

        virtual ::ecore::EAttribute_ptr getETypedElement__lowerBound();

        virtual ::ecore::EAttribute_ptr getETypedElement__upperBound();

        virtual ::ecore::EAttribute_ptr getETypedElement__many();

        virtual ::ecore::EAttribute_ptr getETypedElement__required();

        virtual ::ecore::EReference_ptr getETypedElement__eType();

        virtual ::ecore::EReference_ptr getETypedElement__eGenericType();

        virtual ::ecore::EAttribute_ptr getEStructuralFeature__changeable();

        virtual ::ecore::EAttribute_ptr getEStructuralFeature__volatile();

        virtual ::ecore::EAttribute_ptr getEStructuralFeature__transient();

        virtual ::ecore::EAttribute_ptr
                getEStructuralFeature__defaultValueLiteral();

        virtual ::ecore::EAttribute_ptr getEStructuralFeature__defaultValue();

        virtual ::ecore::EAttribute_ptr getEStructuralFeature__unsettable();

        virtual ::ecore::EAttribute_ptr getEStructuralFeature__derived();

        virtual ::ecore::EReference_ptr
                getEStructuralFeature__eContainingClass();

        virtual ::ecore::EAttribute_ptr getEAttribute__iD();

        virtual ::ecore::EReference_ptr getEAttribute__eAttributeType();

        virtual ::ecore::EAttribute_ptr getEAnnotation__source();

        virtual ::ecore::EReference_ptr getEAnnotation__details();

        virtual ::ecore::EReference_ptr getEAnnotation__eModelElement();

        virtual ::ecore::EReference_ptr getEAnnotation__contents();

        virtual ::ecore::EReference_ptr getEAnnotation__references();

        virtual ::ecore::EAttribute_ptr getEClassifier__instanceClassName();

        virtual ::ecore::EAttribute_ptr getEClassifier__instanceClass();

        virtual ::ecore::EAttribute_ptr getEClassifier__defaultValue();

        virtual ::ecore::EAttribute_ptr getEClassifier__instanceTypeName();

        virtual ::ecore::EReference_ptr getEClassifier__ePackage();

        virtual ::ecore::EReference_ptr getEClassifier__eTypeParameters();

        virtual ::ecore::EAttribute_ptr getEClass__abstract();

        virtual ::ecore::EAttribute_ptr getEClass__interface();

        virtual ::ecore::EReference_ptr getEClass__eSuperTypes();

        virtual ::ecore::EReference_ptr getEClass__eOperations();

        virtual ::ecore::EReference_ptr getEClass__eAllAttributes();

        virtual ::ecore::EReference_ptr getEClass__eAllReferences();

        virtual ::ecore::EReference_ptr getEClass__eReferences();

        virtual ::ecore::EReference_ptr getEClass__eAttributes();

        virtual ::ecore::EReference_ptr getEClass__eAllContainments();

        virtual ::ecore::EReference_ptr getEClass__eAllOperations();

        virtual ::ecore::EReference_ptr getEClass__eAllStructuralFeatures();

        virtual ::ecore::EReference_ptr getEClass__eAllSuperTypes();

        virtual ::ecore::EReference_ptr getEClass__eIDAttribute();

        virtual ::ecore::EReference_ptr getEClass__eStructuralFeatures();

        virtual ::ecore::EReference_ptr getEClass__eGenericSuperTypes();

        virtual ::ecore::EReference_ptr getEClass__eAllGenericSuperTypes();

        virtual ::ecore::EAttribute_ptr getEDataType__serializable();

        virtual ::ecore::EReference_ptr getEEnum__eLiterals();

        virtual ::ecore::EAttribute_ptr getEEnumLiteral__value();

        virtual ::ecore::EAttribute_ptr getEEnumLiteral__instance();

        virtual ::ecore::EAttribute_ptr getEEnumLiteral__literal();

        virtual ::ecore::EReference_ptr getEEnumLiteral__eEnum();

        virtual ::ecore::EReference_ptr getEFactory__ePackage();

        virtual ::ecore::EReference_ptr getEOperation__eContainingClass();

        virtual ::ecore::EReference_ptr getEOperation__eTypeParameters();

        virtual ::ecore::EReference_ptr getEOperation__eParameters();

        virtual ::ecore::EReference_ptr getEOperation__eExceptions();

        virtual ::ecore::EReference_ptr getEOperation__eGenericExceptions();

        virtual ::ecore::EAttribute_ptr getEPackage__nsURI();

        virtual ::ecore::EAttribute_ptr getEPackage__nsPrefix();

        virtual ::ecore::EReference_ptr getEPackage__eFactoryInstance();

        virtual ::ecore::EReference_ptr getEPackage__eClassifiers();

        virtual ::ecore::EReference_ptr getEPackage__eSubpackages();

        virtual ::ecore::EReference_ptr getEPackage__eSuperPackage();

        virtual ::ecore::EReference_ptr getEParameter__eOperation();

        virtual ::ecore::EAttribute_ptr getEReference__containment();

        virtual ::ecore::EAttribute_ptr getEReference__container();

        virtual ::ecore::EAttribute_ptr getEReference__resolveProxies();

        virtual ::ecore::EReference_ptr getEReference__eOpposite();

        virtual ::ecore::EReference_ptr getEReference__eReferenceType();

        virtual ::ecore::EReference_ptr getEReference__eKeys();

        virtual ::ecore::EAttribute_ptr getEStringToStringMapEntry__key();

        virtual ::ecore::EAttribute_ptr getEStringToStringMapEntry__value();

        virtual ::ecore::EReference_ptr getEGenericType__eUpperBound();

        virtual ::ecore::EReference_ptr getEGenericType__eTypeArguments();

        virtual ::ecore::EReference_ptr getEGenericType__eRawType();

        virtual ::ecore::EReference_ptr getEGenericType__eLowerBound();

        virtual ::ecore::EReference_ptr getEGenericType__eTypeParameter();

        virtual ::ecore::EReference_ptr getEGenericType__eClassifier();

        virtual ::ecore::EReference_ptr getETypeParameter__eBounds();

    protected:

        static std::auto_ptr< EcorePackage > s_instance;

        EcorePackage();

        // EClass instances 

        ::ecore::EClass_ptr m_EAttributeEClass;

        ::ecore::EClass_ptr m_EAnnotationEClass;

        ::ecore::EClass_ptr m_EClassEClass;

        ::ecore::EClass_ptr m_EClassifierEClass;

        ::ecore::EClass_ptr m_EDataTypeEClass;

        ::ecore::EClass_ptr m_EEnumEClass;

        ::ecore::EClass_ptr m_EEnumLiteralEClass;

        ::ecore::EClass_ptr m_EFactoryEClass;

        ::ecore::EClass_ptr m_EModelElementEClass;

        ::ecore::EClass_ptr m_ENamedElementEClass;

        ::ecore::EClass_ptr m_EObjectEClass;

        ::ecore::EClass_ptr m_EOperationEClass;

        ::ecore::EClass_ptr m_EPackageEClass;

        ::ecore::EClass_ptr m_EParameterEClass;

        ::ecore::EClass_ptr m_EReferenceEClass;

        ::ecore::EClass_ptr m_EStructuralFeatureEClass;

        ::ecore::EClass_ptr m_ETypedElementEClass;

        ::ecore::EClass_ptr m_EStringToStringMapEntryEClass;

        ::ecore::EClass_ptr m_EGenericTypeEClass;

        ::ecore::EClass_ptr m_ETypeParameterEClass;

        // EEnuminstances 


        // EDataType instances 

        ::ecore::EDataType_ptr m_EBigDecimalEDataType;

        ::ecore::EDataType_ptr m_EBigIntegerEDataType;

        ::ecore::EDataType_ptr m_EBooleanEDataType;

        ::ecore::EDataType_ptr m_EBooleanObjectEDataType;

        ::ecore::EDataType_ptr m_EByteEDataType;

        ::ecore::EDataType_ptr m_EByteArrayEDataType;

        ::ecore::EDataType_ptr m_EByteObjectEDataType;

        ::ecore::EDataType_ptr m_ECharEDataType;

        ::ecore::EDataType_ptr m_ECharacterObjectEDataType;

        ::ecore::EDataType_ptr m_EDateEDataType;

        ::ecore::EDataType_ptr m_EDiagnosticChainEDataType;

        ::ecore::EDataType_ptr m_EDoubleEDataType;

        ::ecore::EDataType_ptr m_EDoubleObjectEDataType;

        ::ecore::EDataType_ptr m_EEListEDataType;

        ::ecore::EDataType_ptr m_EEnumeratorEDataType;

        ::ecore::EDataType_ptr m_EFeatureMapEDataType;

        ::ecore::EDataType_ptr m_EFeatureMapEntryEDataType;

        ::ecore::EDataType_ptr m_EFloatEDataType;

        ::ecore::EDataType_ptr m_EFloatObjectEDataType;

        ::ecore::EDataType_ptr m_EIntEDataType;

        ::ecore::EDataType_ptr m_EIntegerObjectEDataType;

        ::ecore::EDataType_ptr m_EJavaClassEDataType;

        ::ecore::EDataType_ptr m_EJavaObjectEDataType;

        ::ecore::EDataType_ptr m_ELongEDataType;

        ::ecore::EDataType_ptr m_ELongObjectEDataType;

        ::ecore::EDataType_ptr m_EMapEDataType;

        ::ecore::EDataType_ptr m_EResourceEDataType;

        ::ecore::EDataType_ptr m_EResourceSetEDataType;

        ::ecore::EDataType_ptr m_EShortEDataType;

        ::ecore::EDataType_ptr m_EShortObjectEDataType;

        ::ecore::EDataType_ptr m_EStringEDataType;

        ::ecore::EDataType_ptr m_ETreeIteratorEDataType;

        ::ecore::EDataType_ptr m_EInvocationTargetExceptionEDataType;

        // EStructuralFeatures instances

        ::ecore::EReference_ptr m_EModelElement__eAnnotations;

        ::ecore::EAttribute_ptr m_ENamedElement__name;

        ::ecore::EAttribute_ptr m_ETypedElement__ordered;

        ::ecore::EAttribute_ptr m_ETypedElement__unique;

        ::ecore::EAttribute_ptr m_ETypedElement__lowerBound;

        ::ecore::EAttribute_ptr m_ETypedElement__upperBound;

        ::ecore::EAttribute_ptr m_ETypedElement__many;

        ::ecore::EAttribute_ptr m_ETypedElement__required;

        ::ecore::EReference_ptr m_ETypedElement__eType;

        ::ecore::EReference_ptr m_ETypedElement__eGenericType;

        ::ecore::EAttribute_ptr m_EStructuralFeature__changeable;

        ::ecore::EAttribute_ptr m_EStructuralFeature__volatile;

        ::ecore::EAttribute_ptr m_EStructuralFeature__transient;

        ::ecore::EAttribute_ptr m_EStructuralFeature__defaultValueLiteral;

        ::ecore::EAttribute_ptr m_EStructuralFeature__defaultValue;

        ::ecore::EAttribute_ptr m_EStructuralFeature__unsettable;

        ::ecore::EAttribute_ptr m_EStructuralFeature__derived;

        ::ecore::EReference_ptr m_EStructuralFeature__eContainingClass;

        ::ecore::EAttribute_ptr m_EAttribute__iD;

        ::ecore::EReference_ptr m_EAttribute__eAttributeType;

        ::ecore::EAttribute_ptr m_EAnnotation__source;

        ::ecore::EReference_ptr m_EAnnotation__details;

        ::ecore::EReference_ptr m_EAnnotation__eModelElement;

        ::ecore::EReference_ptr m_EAnnotation__contents;

        ::ecore::EReference_ptr m_EAnnotation__references;

        ::ecore::EAttribute_ptr m_EClassifier__instanceClassName;

        ::ecore::EAttribute_ptr m_EClassifier__instanceClass;

        ::ecore::EAttribute_ptr m_EClassifier__defaultValue;

        ::ecore::EAttribute_ptr m_EClassifier__instanceTypeName;

        ::ecore::EReference_ptr m_EClassifier__ePackage;

        ::ecore::EReference_ptr m_EClassifier__eTypeParameters;

        ::ecore::EAttribute_ptr m_EClass__abstract;

        ::ecore::EAttribute_ptr m_EClass__interface;

        ::ecore::EReference_ptr m_EClass__eSuperTypes;

        ::ecore::EReference_ptr m_EClass__eOperations;

        ::ecore::EReference_ptr m_EClass__eAllAttributes;

        ::ecore::EReference_ptr m_EClass__eAllReferences;

        ::ecore::EReference_ptr m_EClass__eReferences;

        ::ecore::EReference_ptr m_EClass__eAttributes;

        ::ecore::EReference_ptr m_EClass__eAllContainments;

        ::ecore::EReference_ptr m_EClass__eAllOperations;

        ::ecore::EReference_ptr m_EClass__eAllStructuralFeatures;

        ::ecore::EReference_ptr m_EClass__eAllSuperTypes;

        ::ecore::EReference_ptr m_EClass__eIDAttribute;

        ::ecore::EReference_ptr m_EClass__eStructuralFeatures;

        ::ecore::EReference_ptr m_EClass__eGenericSuperTypes;

        ::ecore::EReference_ptr m_EClass__eAllGenericSuperTypes;

        ::ecore::EAttribute_ptr m_EDataType__serializable;

        ::ecore::EReference_ptr m_EEnum__eLiterals;

        ::ecore::EAttribute_ptr m_EEnumLiteral__value;

        ::ecore::EAttribute_ptr m_EEnumLiteral__instance;

        ::ecore::EAttribute_ptr m_EEnumLiteral__literal;

        ::ecore::EReference_ptr m_EEnumLiteral__eEnum;

        ::ecore::EReference_ptr m_EFactory__ePackage;

        ::ecore::EReference_ptr m_EOperation__eContainingClass;

        ::ecore::EReference_ptr m_EOperation__eTypeParameters;

        ::ecore::EReference_ptr m_EOperation__eParameters;

        ::ecore::EReference_ptr m_EOperation__eExceptions;

        ::ecore::EReference_ptr m_EOperation__eGenericExceptions;

        ::ecore::EAttribute_ptr m_EPackage__nsURI;

        ::ecore::EAttribute_ptr m_EPackage__nsPrefix;

        ::ecore::EReference_ptr m_EPackage__eFactoryInstance;

        ::ecore::EReference_ptr m_EPackage__eClassifiers;

        ::ecore::EReference_ptr m_EPackage__eSubpackages;

        ::ecore::EReference_ptr m_EPackage__eSuperPackage;

        ::ecore::EReference_ptr m_EParameter__eOperation;

        ::ecore::EAttribute_ptr m_EReference__containment;

        ::ecore::EAttribute_ptr m_EReference__container;

        ::ecore::EAttribute_ptr m_EReference__resolveProxies;

        ::ecore::EReference_ptr m_EReference__eOpposite;

        ::ecore::EReference_ptr m_EReference__eReferenceType;

        ::ecore::EReference_ptr m_EReference__eKeys;

        ::ecore::EAttribute_ptr m_EStringToStringMapEntry__key;

        ::ecore::EAttribute_ptr m_EStringToStringMapEntry__value;

        ::ecore::EReference_ptr m_EGenericType__eUpperBound;

        ::ecore::EReference_ptr m_EGenericType__eTypeArguments;

        ::ecore::EReference_ptr m_EGenericType__eRawType;

        ::ecore::EReference_ptr m_EGenericType__eLowerBound;

        ::ecore::EReference_ptr m_EGenericType__eTypeParameter;

        ::ecore::EReference_ptr m_EGenericType__eClassifier;

        ::ecore::EReference_ptr m_ETypeParameter__eBounds;

    };

} // ecore


#endif // _ECOREPACKAGE_HPP
