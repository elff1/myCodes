<?php

class TestInfoComponent extends CApplicationComponent {
	
	/**
	 * @obsolete not implemented
	 * @param integer $proId
	 */
	public static function delRecordingByProId($proId) {
		$submit_ignore = true;
		$paperProbPairs = Paper::model ()->with ( "testRecording", "paper.stuTestStatuses" )->findAllByAttributes ( array (
				'pro_id' => $proId,'StuTestStatus.is_submit'=>0
		) );
		foreach ( $paperProbPairs as $paperProbPair ) {
			echo $paperProbPair->id;
			//$recordings = $paperProbPair->testRecordings;
			//$testStatuses = $paperProbPair->paper->stuTestStatuses;
			
		}
	}
	/**
	 *
	 * @param integer $paperId        	
	 * @return problems in specific paper as ActiveDataProvider
	 * @uses by ployee
	 */
	public static function getQuestionByPaper($paperId) {
		$condi = new CDbCriteria ();
		$condi->compare ( 'paper_id', $paperId );
		$paperProbPairs = Paper::model ()->findAll ( $condi );
		$data = array ();
		foreach ( $paperProbPairs as $i => $paperProbPair ) {
			$data [$i] = $paperProbPair->pro;
		}
		return new CArrayDataProvider ( $data );
	}
	
	/**
	 * @param integer $stuId
	 * @return key-value array:number paperId=>paperScore
	 * FIXME: circumstances in which a student has submit test but no problems done, so no test-recording
	 * FIXME: if not submit, should not count it
	 */
	public static function getStudentScore($stuId) {
		$ret = array ();
		$recordings = TestRecording::model ()->findAllByAttributes ( array (
				"student_id" => $stuId 
		) );
		
		$statuses = StuTestStatus::model ()->findAllByAttributes ( array (
				'stu_id' => $stuId,
		) );
		foreach($statuses as $status)
		{
			$ret [$status ->paper_id] = 0;
		}
		foreach ( $recordings as $recording ) {
			$paperProp = $recording->paperPro;
			$paperId = $paperProp->paper_id;
			$status = StuTestStatus::model ()->findByAttributes ( array (
				'stu_id' => $stuId,
				'paper_id' => $paperId 
		) );
			if (isset ( $ret [$paperId] )) {
				if ($recording->choose === $paperProp->pro->answer) {
					$ret [$paperId] = $ret [$paperId] + $paperProp->pro_score;
				}
			}
		}
		return $ret;
	}
}

?>