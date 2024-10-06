
CREATE TABLE IF NOT EXISTS qcril_properties_table (property TEXT, def_val TEXT, value TEXT, PRIMARY KEY(property));
UPDATE qcril_properties_table set value='46' where property='qcrildb_version';

DELETE FROM qcril_emergency_source_mcc_mnc_table where MCC = '740' AND MNC = '01' AND NUMBER = '101';
DELETE FROM qcril_emergency_source_mcc_mnc_table where MCC = '740' AND MNC = '02' AND NUMBER = '101';
DELETE FROM qcril_emergency_source_mcc_mnc_table where MCC = '740' AND MNC = '00' AND NUMBER = '123';

INSERT OR REPLACE INTO "qcril_emergency_source_mcc_mnc_table" VALUES('740','01','123','','');

