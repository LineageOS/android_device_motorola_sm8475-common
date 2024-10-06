CREATE TABLE IF NOT EXISTS qcril_properties_table (property TEXT, def_val TEXT, value TEXT, PRIMARY KEY(property));

UPDATE qcril_properties_table set value='41' where property='qcrildb_version';

DELETE FROM qcril_emergency_source_voice_mcc_mnc_table where MCC = '228' AND MNC = '01' AND NUMBER = '117';
DELETE FROM qcril_emergency_source_voice_mcc_mnc_table where MCC = '228' AND MNC = '01' AND NUMBER = '118';
DELETE FROM qcril_emergency_source_voice_mcc_mnc_table where MCC = '228' AND MNC = '01' AND NUMBER = '143';
DELETE FROM qcril_emergency_source_voice_mcc_mnc_table where MCC = '228' AND MNC = '01' AND NUMBER = '144';
DELETE FROM qcril_emergency_source_voice_mcc_mnc_table where MCC = '228' AND MNC = '01' AND NUMBER = '145';
DELETE FROM qcril_emergency_source_voice_mcc_mnc_table where MCC = '228' AND MNC = '01' AND NUMBER = '147';

INSERT OR REPLACE INTO "qcril_emergency_source_mcc_mnc_table" VALUES('228','01','117','','');
INSERT OR REPLACE INTO "qcril_emergency_source_mcc_mnc_table" VALUES('228','01','118','','');
INSERT OR REPLACE INTO "qcril_emergency_source_mcc_mnc_table" VALUES('228','01','143','','');
INSERT OR REPLACE INTO "qcril_emergency_source_mcc_mnc_table" VALUES('228','01','144','','');
INSERT OR REPLACE INTO "qcril_emergency_source_mcc_mnc_table" VALUES('228','01','145','','');
INSERT OR REPLACE INTO "qcril_emergency_source_mcc_mnc_table" VALUES('228','01','147','','');
INSERT OR REPLACE INTO "qcril_emergency_source_mcc_mnc_table" VALUES('228','02','1414','','');
INSERT OR REPLACE INTO "qcril_emergency_source_mcc_mnc_table" VALUES('228','03','1414','','');
