<div class="form">

<?php $form=$this->beginWidget('CActiveForm', array(
	'id'=>'course-waitlist-form',
	'enableAjaxValidation'=>false,
)); ?>

	<p class="note"><?php
	echo InformationManagementModule::t('other','Fields with <span class="required">*</span> are required.'); /* no CHtml::encode here*/?></p>

	<?php echo $form->errorSummary($model); ?>

	<div class="row">
		<?php echo $form->labelEx($model,'name'); ?>
		<?php echo $form->textField($model,'name',array('size'=>32,'maxlength'=>32)); ?>
		<?php echo $form->error($model,'name'); ?>
	</div>

	<div class="row">
		<?php echo $form->labelEx($model,'credit'); ?>
		<?php echo $form->textField($model,'credit'); ?>
		<?php echo $form->error($model,'credit'); ?>
	</div>

	<div class="row">
		<?php echo $form->labelEx($model,'class'); ?>
		<?php echo $form->textField($model,'class'); ?>
		<?php echo $form->error($model,'class'); ?>
	</div>

	<div class="row">
		<?php echo $form->labelEx($model,'prerequsite_required'); ?>
		<?php echo $form->textField($model,'prerequsite_required'); ?>
		<?php echo $form->error($model,'prerequsite_required'); ?>
	</div>

	<div class="row">
		<?php echo $form->labelEx($model,'introduction'); ?>
		<?php echo $form->textField($model,'introduction',array('size'=>60,'maxlength'=>2048)); ?>
		<?php echo $form->error($model,'introduction'); ?>
	</div>

	<div class="row">
		<?php echo $form->labelEx($model,'syllabus'); ?>
		<?php echo $form->textField($model,'syllabus',array('size'=>60,'maxlength'=>2048)); ?>
		<?php echo $form->error($model,'syllabus'); ?>
	</div>

	<div class="row">
		<?php echo $form->labelEx($model,'statement'); ?>
		<?php echo $form->textField($model,'statement',array('size'=>60,'maxlength'=>2048)); ?>
		<?php echo $form->error($model,'statement'); ?>
	</div>

	<div class="row">
		<?php echo $form->labelEx($model,'department_id'); ?>
		<?php echo $form->dropDownList($model,'department_id',Department::model()->departmentList); ?>
		<?php echo $form->error($model,'department_id'); ?>
	</div>

	<div class="row">
		<?php echo $form->labelEx($model,'priority'); ?>
		<?php echo $form->textField($model,'priority'); ?>
		<?php echo $form->error($model,'priority'); ?>
	</div>

	<div class="row buttons">
		<?php echo CHtml::submitButton($model->isNewRecord ? Yii::t('base','Create'):Yii::t('base','Save')); ?>
	</div>

<?php $this->endWidget(); ?>

</div><!-- form -->