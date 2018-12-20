TEMPLATE = subdirs

SUBDIRS += \
    FractionLib \
    FractionTests

FractionTests.depends = FractionLib
