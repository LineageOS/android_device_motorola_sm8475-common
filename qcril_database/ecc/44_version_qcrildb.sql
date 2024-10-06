
CREATE TABLE IF NOT EXISTS qcril_properties_table (property TEXT, def_val TEXT, value TEXT, PRIMARY KEY(property));
UPDATE qcril_properties_table set value='44' where property='qcrildb_version';

INSERT OR REPLACE INTO "qcril_emergency_source_mcc_table" VALUES('420','993','','');
INSERT OR REPLACE INTO "qcril_emergency_source_mcc_table" VALUES('420','997','','');
INSERT OR REPLACE INTO "qcril_emergency_source_mcc_table" VALUES('420','998','','');
INSERT OR REPLACE INTO "qcril_emergency_source_mcc_table" VALUES('420','999','','');

